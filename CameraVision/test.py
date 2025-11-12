
from ultralytics import YOLO
import cv2

from utils import keypoint_labels, isSitting

def format_keypoints_from_result(result):
    out = []
    if (len(result.keypoints.xy) > 0):
        for person in result.keypoints.xy:
            p = []
            for v in person:
                p.append((round(float(v[0]), 1), round(float(v[1]), 1)))
            out.append(p)
    print(len(out))
    return out

def print_keypoints(keypoints):

    for v, label in zip(keypoints, keypoint_labels):
        if (label != "Nose"): continue

        while len(label) < 14:
            label += " "

        print(f"{label}: {v}")

def main():
    model = YOLO("yolo11n-pose.pt")
    cap = cv2.VideoCapture(0)

    if not cap.isOpened():
        print("Error: Could not open webcam.")
        return

    while True:
        ret, frame = cap.read()
        if not ret:
            break

        # Run inference
        result = model(frame, verbose=False)[0]

        list_sitting = []
        people = format_keypoints_from_result(result)
        for keypoints in people:
            if len(keypoints) != 0:
                list_sitting.append(isSitting(keypoints))

        annotated_frame = result.plot()

        for i, b in enumerate(list_sitting):
            text = "Standing" if b else "Sitting"
            color = (255, 0, 0) if b else (0, 255, 0)
            cv2.putText(annotated_frame, text, (20, 50 + 50 * i), cv2.FONT_HERSHEY_SIMPLEX, 1.5, color, 2)

        cv2.imshow("YOLO Pose Detection", annotated_frame)

        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    cap.release()
    cv2.destroyAllWindows()

if __name__ == "__main__":
    main()
