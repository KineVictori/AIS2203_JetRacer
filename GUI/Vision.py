# This file is made by ChatGPT

from __future__ import annotations
from typing import Optional
import numpy as np
import cv2

# Import the compiled pybind11 module
import VisionPython


class VisionClient:
    """
    Python wrapper around the native VisionPython.visionClient class.
    Handles image decoding automatically.
    """

    def __init__(self, ip: str, port: int) -> None:
        """
        Connect to the remote vision server.

        Args:
            ip (str): The IP address of the server.
            port (int): The port number to connect to.
        """
        self._native = VisionPython.visionClient(ip, port)

    def getFrame(self) -> Optional[np.ndarray]:
        """
        Get the latest frame from the vision client as an OpenCV image (BGR).

        Returns:
            np.ndarray | None: The decoded frame as a NumPy array, or None if no frame is available.
        """
        data = self._native.getFrame()
        if not data:
            return None

        arr = np.frombuffer(bytes(data), dtype=np.uint8)
        frame = cv2.imdecode(arr, cv2.IMREAD_COLOR)
        return frame

    def __repr__(self) -> str:
        return f"<VisionClient connected to native VisionPython>"
