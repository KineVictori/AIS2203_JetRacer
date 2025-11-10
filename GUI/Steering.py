
# This file is made by ChatGPT

"""
High-level Python wrapper for the Steering C++ bindings.
Provides autocompletion and docstrings for editors.
"""

from __future__ import annotations

# Import the compiled PyBind11 extension
from SteeringPython import Steering as _Steering, SteeringData as _SteeringData


class SteeringData:
    """Container for steering and throttle parameters."""

    def __init__(
            self,
            steering: float = 0.0,
            throttle: float = 0.0,
            steering_gain: float = 1.0,
            throttle_gain: float = 1.0,
            steering_offset: float = 0.0,
    ):
        """Initialize a SteeringData structure."""
        self._data = _SteeringData()
        self._data.steering = steering
        self._data.throttle = throttle
        self._data.steering_gain = steering_gain
        self._data.throttle_gain = throttle_gain
        self._data.steering_offset = steering_offset

    # Properties for IDE autocompletion
    @property
    def steering(self) -> float: return self._data.steering
    @steering.setter
    def steering(self, v: float): self._data.steering = v

    @property
    def throttle(self) -> float: return self._data.throttle
    @throttle.setter
    def throttle(self, v: float): self._data.throttle = v

    @property
    def steering_gain(self) -> float: return self._data.steering_gain
    @steering_gain.setter
    def steering_gain(self, v: float): self._data.steering_gain = v

    @property
    def throttle_gain(self) -> float: return self._data.throttle_gain
    @throttle_gain.setter
    def throttle_gain(self, v: float): self._data.throttle_gain = v

    @property
    def steering_offset(self) -> float: return self._data.steering_offset
    @steering_offset.setter
    def steering_offset(self, v: float): self._data.steering_offset = v

    def _unwrap(self) -> _SteeringData:
        """Return the underlying C++ object (internal use)."""
        return self._data


class Steering:
    """Pythonic wrapper around the C++ Steering class."""

    def __init__(self, ip: str, port: int):
        """
        Initialize the steering communication.

        Args:
            ip: Target IP address.
            port: Target port number.
        """
        self._impl = _Steering(ip, port)

    def isReady(self):
        return self._impl.isReady()

    def sendData(self, data: SteeringData) -> None:
        """Send steering and throttle data."""
        self._impl.sendData(data._unwrap())


__all__ = ["Steering", "SteeringData"]
