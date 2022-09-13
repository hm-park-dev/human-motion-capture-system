
# IMPORT
import math
from blue_st_sdk.feature import Sample
from blue_st_sdk.feature import ExtractedData
from blue_st_sdk.features.field import Field
from blue_st_sdk.features.field import FieldType
from blue_st_sdk.utils.number_conversion import LittleEndian
from blue_st_sdk.utils.blue_st_exceptions import BlueSTInvalidDataException

from blue_st_sdk.features.feature_auto_configurable import FeatureAutoConfigurable

class FeatureMemsSensorFusion(FeatureAutoConfigurable):
    '''
    This feature will contains the quaternion compute 
    in the device using the sensor fusion algorithm
    (gyroscope + accelerometer + magnetometer).
    
    The data will be transfer using float data for each component.
    the quaternion components are normalized to 1
    Qi = x component, Qj = y component Qk = z component Qs = scalar component
    The AutoConfigure process will acquire the magnetometer data for calibrate the magnetometer
    '''
    FEATURE_NAME = "MEMS Sensor Fusion"
    FEATURE_UNIT = ""
    FEATURE_DATA_NAME = ["qi", "qj", "qk", "qs"]
    DATA_MAX = float(1)
    DATA_MIN = float(-1)
    QI_INDEX = 0
    QJ_INDEX = 1
    QK_INDEX = 2
    QS_INDEX = 3
    FEATURE_QI_FIELD = Field(
        FEATURE_DATA_NAME[QI_INDEX],
        FEATURE_UNIT,
        FieldType.Float,
        DATA_MAX,
        DATA_MIN)
    FEATURE_QJ_FIELD = Field(
        FEATURE_DATA_NAME[QJ_INDEX],
        FEATURE_UNIT,
        FieldType.Float,
        DATA_MAX,
        DATA_MIN)
    FEATURE_QK_FIELD = Field(
        FEATURE_DATA_NAME[QK_INDEX],
        FEATURE_UNIT,
        FieldType.Float,
        DATA_MAX,
        DATA_MIN)
    FEATURE_QS_FIELD = Field(
        FEATURE_DATA_NAME[QS_INDEX],
        FEATURE_UNIT,
        FieldType.Float,
        DATA_MAX,
        DATA_MIN)
    
    DATA_LENGTH_BYTES = 12
    ADDITIONAL_DATA_LENGTH_BYTES = 4

    def __init__(self, node, name=None):
        if name is not None:
            self.FEATURE_NAME = name
        super(FeatureMemsSensorFusion, self).__init__(
            self.FEATURE_NAME, node, [self.FEATURE_QI_FIELD,
                                      self.FEATURE_QJ_FIELD,
                                      self.FEATURE_QK_FIELD,
                                      self.FEATURE_QS_FIELD])
    
    @classmethod
    def get_Qi(self, sample):
        '''
        Get the quaternion qi component
        @param sample sample data from the sensor
        '''
        if sample is not None:
            if sample._data[self.QI_INDEX] is not None:
                return float(sample._data[self.QI_INDEX])
        return float('nan')

    @classmethod
    def get_Qj(self, sample):
        if sample is not None:
            if sample._data[self.QJ_INDEX] is not None:
                return float(sample._data[self.QJ_INDEX])
        return float('nan')

    @classmethod
    def get_Qk(self, sample):
        if sample is not None:
            if sample._data[self.QK_INDEX] is not None:
                return float(sample._data[self.QK_INDEX])
        return float('nan')

    @classmethod
    def get_Qs(self, sample):
        if sample is not None:
            if sample._data[self.QS_INDEX] is not None:
                return float(sample._data[self.QS_INDEX])
        return float('nan')

    def _compute_Qs(self, qi, qj, qk):
        t = float(1) - (qi * qi + qj * qj + qk * qk)
        if t > 0 :
            return math.sqrt(t)
        else:
            return 0

    def extract_data(self, timestamp, data, offset):
        if len(data) - offset < self.DATA_LENGTH_BYTES:
            raise BlueSTInvalidDataException(
                'There are no %s bytes available to read.' \
                % (self.DATA_LENGTH_BYTES))

        qi = LittleEndian.bytes_to_float(data, offset)
        qj = LittleEndian.bytes_to_float(data, offset + 4)
        qk = LittleEndian.bytes_to_float(data, offset + 8)

        nReadByte = self.DATA_LENGTH_BYTES

        if len(data) - offset > self.DATA_LENGTH_BYTES:
            qs = LittleEndian.bytes_to_float(data, offset + 12)
            # Normalize the quaternion
            norm = math.sqrt(qi*qi + qj*qj + qk*qk + qs*qs)
            qi /= norm
            qj /= norm
            qk /= norm
            qs /= norm

            nReadByte += 4
        else:
            qs = self._compute_Qs(qi, qj, qk)
            
        sample = Sample([qi, qj, qk, qs],
            self.get_fields_description(),
            timestamp)

        return ExtractedData(sample, nReadByte)

#FeatureMemsSensorFusion