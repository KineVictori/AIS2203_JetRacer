from Vision import VisionClient
from Steering import Steering, SteeringData


class MiddleMan:
    def __init__(self):
        self.steering = Steering("10.22.23.202", 43457)
        self.visionClient = VisionClient("10.22.23.202", 45678)

    
    def SendDataToCar(self, data):
        if self.steering.isReady():
            self.steering.sendData(data)
        else:                                       #gui skal bruke denne for å sende data.
            pass

    def GetDataFromCar(self):
        if self.visionClient.isReady():
            return self.visionClient.getFrame()
        else:                                       #gui skal bruke denne til å hente data. 
            None

