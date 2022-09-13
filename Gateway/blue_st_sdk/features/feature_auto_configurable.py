# IMPORT

from abc import abstractmethod
from blue_st_sdk.feature import Feature
from blue_st_sdk.feature import FeatureListener

# CLASSES
class FeatureAutoConfigurable(Feature):
    
    # value used for start the configuration procedure
    FEATURE_COMMAND_START_CONFIG = 0x00

    # value used for stop the configuration procedure
    FEATURE_COMMAND_STOP_CONFIG = 0x01

    # value used for ask the current configuration status/goodness
    FEATURE_COMMAND_GET_CONFIG_STATUS = 0xFF

    def __init__(self, name, node, description):
        """Constructor.

        Args:
            node (:class:`blue_st_sdk.node.Node`): Node that will send data to
                this feature.
        """
        super(FeatureAutoConfigurable, self).__init__(name, node, description)

        '''
        * tell if the feature is configured, in the node side.
        * if it is false it you have to call {@link FeatureAutoConfigurable#startAutoConfiguration()} before
        * have correct values
        * default value: true
        '''
        self._is_configured = None


    def notifyAutoConfigurationStart(self):
        '''
        call the method for each listener that subscribe to this feature.
        each call will be run in a different thread
        '''
        for listener in self._listeners:
            if isinstance(listener, FeatureAutoConfigurationListener):
                # run listener
                self._thread_pool.submit(listener.on_autoConfigurationStart(self))

    
    def notifyAutoConfigurationStatus(self, status):
        '''
        call the method for each listener that subscribe to this feature.
        each call will be run in a different thread
        @param status status of the initialization process, 0 = not started 100=completed
        '''
        for listener in self._listeners:
            if isinstance(listener, FeatureAutoConfigurationListener):
                self._thread_pool.submit(listener.on_autoConfigurationStatusChanged(self, status))

    
    def notifyConfigurationFinished(self, status):
        '''
        call the method for each listener that subscribe to this feature.
        each call will be run in a different thread
        status last status of the calibration process, 0 = not started 100=completed
        '''
        for listener in self._listeners:
            if isinstance(listener, FeatureAutoConfigurationListener):
                self._thread_pool.submit(listener.on_configurationFinished(self, status))

    def startConfiguration(self, data):
        self.setConfigurationStatus(False)
        msgSend = self._send_command(self.FEATURE_COMMAND_START_CONFIG, data)
        if msgSend:
            self.notifyAutoConfigurationStart()
        return msgSend

    def parseCommandResponse(self, timestamp, commandType, data):
        status = data[0]
        if commandType == self.FEATURE_COMMAND_STOP_CONFIG:
            self.notifyConfigurationFinished(status)
            if status == 100:
                self.setConfigurationStatus(True)
        elif commandType == self.FEATURE_COMMAND_GET_CONFIG_STATUS:
            self.notifyAutoConfigurationStatus(status)
            if status == 100:
                self.setConfigurationStatus(True)
                self.notifyConfigurationFinished(status)
            elif status == 0:
                self.setConfigurationStatus(False)
        else:
            print('parse Cmd Resp method called')
            pass

    def startAutoConfiguration(self):
        self.startConfiguration()
    
    def stopAutoConfiguration(self):
        print('stop AutoConfig')
        self._send_command(self.FEATURE_COMMAND_STOP_CONFIG, None)

    def requestAutoConfigurationStatus(self):
        print('request AutoConfig Status')
        self._send_command(self.FEATURE_COMMAND_GET_CONFIG_STATUS, None)
        #raise BlueSTInvalidOperationException

    def setConfigurationStatus(self, status):
        self._is_configured = status

    def isConfigured(self):
        return self._is_configured


class FeatureAutoConfigurationListener(FeatureListener):
    @abstractmethod
    def on_autoConfigurationStart(self, feature):
        '''
         * The feature has start a process for self configuration
         * @Args:
            feature     feature that start the configuration process
        '''
        raise NotImplementedError(
            'You must implement "on_autoConfigurationStart()" to use the "FeatureAutoConfigurationListener" class.')

    @abstractmethod
    def on_autoConfigurationStatusChanged(self, feature, status):
        '''
        * Notify that the process of configuration has a new state
        *
        * @param feature    feature that change its configuration status
        * @param status     new calibration status when reach 100 the configuration is completed
        '''
        raise NotImplementedError(
            'You must implement "on_autoConfigurationStatusChanged()" to use the "FeatureAutoConfigurationListener" class.')        

    @abstractmethod
    def on_configurationFinished(self, feature, status):
        '''
        * The configuration process is done or stopped by the user
        *
        * @param feature  feature that finish its configuration process
        * @param status   final configuration status: -1 if there was an error,
        *                 otherwise is a % with the configuration goodness
        '''
        raise NotImplementedError(
            'You must implement "on_configurationFinished()" to use the "FeatureAutoConfigurationListener" class.')        