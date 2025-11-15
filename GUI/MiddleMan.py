from Vision import VisionClient
from Steering import Steering, SteeringData


class MiddleMan:
    def __init__(self):
        ip = "10.24.15.153"
        self.steering = Steering(ip, 43457)
        self.visionClient = VisionClient(ip, 45678)

    
    def SendDataToCar(self, data):
        if self.steering.isReady():
            self.steering.sendData(data)
        else:                                       #gui skal bruke denne for å sende data.
            pass

    def GetDataFromCar(self):
        if self.visionClient.isReady():
            return self.visionClient.getFrame()
        else:
            return None                 #gui skal bruke denne til å hente data. 
            

