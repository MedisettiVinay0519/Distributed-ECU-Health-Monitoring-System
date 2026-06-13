import joblib
import pandas as pd

model = joblib.load(
    "best_fault_prediction_model.pkl"
)

encoder = joblib.load(
    "label_encoder.pkl"
)

sample = pd.DataFrame(
    {
        "Temperature": [92.0],
        "Voltage": [11.2],
        "Current": [14.0]
    }
)

prediction = model.predict(sample)

predicted_state = encoder.inverse_transform(
    prediction
)

print("\n===== ECU HEALTH PREDICTION =====")

print(sample)

print(
    "\nPredicted State:",
    predicted_state[0]
)