# IMPORT

import threading
import time

from blue_st_sdk.feature import Feature
from blue_st_sdk.feature import Sample
from blue_st_sdk.feature import ExtractedData
from blue_st_sdk.features.field import Field
from blue_st_sdk.features.field import FieldType
from blue_st_sdk.utils.number_conversion import LittleEndian
from blue_st_sdk.utils.python_utils import lock
from blue_st_sdk.utils.blue_st_exceptions import BlueSTInvalidOperationException
from blue_st_sdk.utils.blue_st_exceptions import BlueSTInvalidDataException

from blue_st_sdk.features.feature_mems_sensor_fusion import FeatureMemsSensorFusion

# CLASSES
class FeatureMemsSensorFusionCompact(FeatureMemsSensorFusion):
    '''
    This feature manage the quaternion data in the compact way, in this package the quaternion
    component are encoded using a int16 with  5 decimal values, and sent in group of 2-4 quaternions

    the quaternion are normalized, so the sum of the square is 1
    we assume to receive one package each QUATERNION_DELAY_MS,
    to the user we will notify one quaternion each QUATERNION_DELAY_MS/quaternion

    The AutoConfigure process will acquire the magnetometer data for calibrate the magnetometer sensors
    '''

    FEATURE_NAME = "MEMS Sensor Fusion (Compact)"

    QUATERNION_DELAY_MS = 30
    DATA_LENGTH_BYTES = 6
    SCALE_FACTOR = 10000.0

    def __init__(self, node):
        super(FeatureMemsSensorFusionCompact, self).__init__(node, self.FEATURE_NAME)
    
    def extract_data(self, timestamp, data, offset):
        if len(data) - offset < self.DATA_LENGTH_BYTES:
            raise BlueSTInvalidDataException(
                'There are no %s bytes available to read.' \
                % (self.DATA_LENGTH_BYTES))
        
        nQuat = int( (len(data) - offset) / self.DATA_LENGTH_BYTES)
        quatDelay = float(self.QUATERNION_DELAY_MS) / nQuat
        parsedData = data[offset:offset+self.DATA_LENGTH_BYTES*nQuat]
        #print('len : ' + str(len(data)) + ', offset : ' + str(offset))
        #print('buffered ' + str(nQuat) + 'data ' + str(quatDelay))

        # for i in range(nQuat):
        #     qi = LittleEndian.bytes_to_int16(data, offset) / self.SCALE_FACTOR
        #     qj = LittleEndian.bytes_to_int16(data, offset+2) / self.SCALE_FACTOR
        #     qk = LittleEndian.bytes_to_int16(data, offset+4) / self.SCALE_FACTOR
        #     qs = self._compute_Qs(qi, qj, qk)

        #     if i == 0 :
        #         self._notif_sample(timestamp, qi, qj, qk, qs, parsedData)
        #     else:
        #         DelayUpdate(self, i*quatDelay, timestamp + i, qi, qj, qk, qs)
        #     offset += self.DATA_LENGTH_BYTES

        sendMsgStr = ""
        for i in range(nQuat):
            qi = LittleEndian.bytes_to_int16(data, offset) / self.SCALE_FACTOR
            qj = LittleEndian.bytes_to_int16(data, offset+2) / self.SCALE_FACTOR
            qk = LittleEndian.bytes_to_int16(data, offset+4) / self.SCALE_FACTOR
            qs = self._compute_Qs(qi, qj, qk)

            if i == 2:
                sendMsgStr += f"{qi},{qj},{qk},{qs},{timestamp+i}"
                self._notif_string(sendMsgStr)
            else:
                sendMsgStr += f"{qi},{qj},{qk},{qs},{timestamp+i},"
            offset += self.DATA_LENGTH_BYTES

        return ExtractedData(None, nQuat * self.DATA_LENGTH_BYTES)

    def _notif_sample(self, timestamp, qi, qj, qk, qs, raw):
        with lock(self):
            self._last_sample = Sample([qi, qj, qk, qs], self.get_fields_description(), timestamp)
            newSample = self._last_sample
        self._notify_update(newSample)
        self._log_update(raw, newSample)


class DelayUpdate():
    
    def __init__(self, feature, delayed, timestamp, qi, qj, qk, qs):
        self.feature = feature        
        self.timestamp = timestamp
        self.qi = qi
        self.qj = qj
        self.qk = qk
        self.qs = qs

        th = threading.Timer(delayed/1000, self.update)
        th.start()

    def update(self):
        #print('buffered data')
        self.feature._notif_sample(self.timestamp, self.qi, self.qj, self.qk, self.qs, None)
