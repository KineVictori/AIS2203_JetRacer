
keypoint_labels = [
    "Nose",
    "Left Eye",
    "Right Eye",
    "Left Ear",
    "Right Ear",
    "Left Shoulder",
    "Right Shoulder",
    "Left Elbow",
    "Right Elbow",
    "Left Wrist",
    "Right Wrist",
    "Left Hip",
    "Right Hip",
    "Left Knee",
    "Right Knee",
    "Left Ankle",
    "Right Ankle"
]

def isSitting(keypoints, scale: float = 1.5):

    left_shoulder = keypoints[5][1]
    right_shoulder = keypoints[6][1]

    left_hip = keypoints[11][1]
    right_hip = keypoints[12][1]

    left_knee = keypoints[13][1]
    right_knee = keypoints[14][1]

    dist_left_top = left_shoulder - left_hip
    dist_right_top = right_shoulder - right_hip

    dist_left_bottom = left_hip - left_knee
    dist_right_bottom = right_hip - right_knee

    return (dist_left_top > scale * dist_left_bottom) and (dist_right_top > scale * dist_right_bottom)