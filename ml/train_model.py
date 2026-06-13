import pandas as pd
import numpy as np
import joblib
import matplotlib.pyplot as plt
import seaborn as sns


from sklearn.metrics import ConfusionMatrixDisplay

from sklearn.model_selection import train_test_split
from sklearn.preprocessing import LabelEncoder

from sklearn.linear_model import LogisticRegression
from sklearn.tree import DecisionTreeClassifier
from sklearn.ensemble import (
    RandomForestClassifier,
    GradientBoostingClassifier
)

from sklearn.metrics import (
    accuracy_score,
    precision_score,
    recall_score,
    f1_score,
    classification_report,
    confusion_matrix
)

# =====================================================
# LOAD DATASET
# =====================================================

df = pd.read_csv("ecu_log.csv")

print("Dataset Shape:", df.shape)
print(df.head())

# =====================================================
# FEATURE SELECTION
# =====================================================

X = df[
    [
        "Temperature",
        "Voltage",
        "Current"
    ]
]

y = df["State"]

# =====================================================
# LABEL ENCODING
# =====================================================

encoder = LabelEncoder()

y_encoded = encoder.fit_transform(y)

# =====================================================
# TRAIN TEST SPLIT
# =====================================================

X_train, X_test, y_train, y_test = train_test_split(
    X,
    y_encoded,
    test_size=0.20,
    random_state=42,
    stratify=y_encoded
)

# =====================================================
# MODELS
# =====================================================

models = {

    "Logistic Regression":
        LogisticRegression(
            max_iter=1000
        ),

    "Decision Tree":
        DecisionTreeClassifier(
            random_state=42
        ),

    "Random Forest":
        RandomForestClassifier(
            n_estimators=100,
            random_state=42
        ),

    "Gradient Boosting":
        GradientBoostingClassifier(
            random_state=42
        )
}

# =====================================================
# TRAINING + EVALUATION
# =====================================================

results = []

best_model = None
best_accuracy = 0
best_model_name = ""

for name, model in models.items():

    model.fit(
        X_train,
        y_train
    )

    predictions = model.predict(
        X_test
    )

    accuracy = accuracy_score(
        y_test,
        predictions
    )

    precision = precision_score(
        y_test,
        predictions,
        average="weighted"
    )

    recall = recall_score(
        y_test,
        predictions,
        average="weighted"
    )

    f1 = f1_score(
        y_test,
        predictions,
        average="weighted"
    )

    results.append([
        name,
        accuracy,
        precision,
        recall,
        f1
    ])

    print("\n" + "=" * 60)
    print(name)
    print("=" * 60)

    print(
        classification_report(
            y_test,
            predictions,
            target_names=encoder.classes_
        )
    )

    print(
        "Confusion Matrix:\n",
        confusion_matrix(
            y_test,
            predictions
        )
    )

    if accuracy > best_accuracy:

        best_accuracy = accuracy
        best_model = model
        best_model_name = name

# =====================================================
# RESULTS TABLE
# =====================================================

results_df = pd.DataFrame(
    results,
    columns=[
        "Model",
        "Accuracy",
        "Precision",
        "Recall",
        "F1 Score"
    ]
)

results_df = results_df.sort_values(
    by="Accuracy",
    ascending=False
)

print("\n")
print("=" * 60)
print("MODEL COMPARISON")
print("=" * 60)
print(results_df)

# =====================================================
# SAVE BEST MODEL
# =====================================================

joblib.dump(
    best_model,
    "best_fault_prediction_model.pkl"
)
joblib.dump(
    encoder,
    "label_encoder.pkl"
)

print("\nBest Model :", best_model_name)
print("Best Accuracy :", round(best_accuracy, 4))
print("Model Saved : best_fault_prediction_model.pkl")

# =====================================================
# PLOT COMPARISON
# =====================================================

plt.figure(figsize=(10, 6))

plt.bar(
    results_df["Model"],
    results_df["Accuracy"]
)

plt.title(
    "Machine Learning Model Comparison"
)

plt.ylabel(
    "Accuracy"
)

plt.xlabel(
    "Models"
)

plt.xticks(rotation=15)

plt.tight_layout()

plt.show()

# =====================================================
# CORRELATION HEATMAP
# =====================================================

numeric_df = df.copy()

numeric_df["State"] = encoder.fit_transform(
    numeric_df["State"]
)

plt.figure(figsize=(8,6))

sns.heatmap(
    numeric_df.corr(),
    annot=True,
    cmap="coolwarm",
    fmt=".2f"
)

plt.title(
    "Correlation Heatmap"
)

plt.tight_layout()

plt.show()


# =====================================================
# CLASS DISTRIBUTION
# =====================================================

plt.figure(figsize=(6,5))

sns.countplot(
    x="State",
    data=df
)

plt.title(
    "Class Distribution"
)

plt.xlabel(
    "ECU State"
)

plt.ylabel(
    "Count"
)

plt.tight_layout()

plt.show()


# =====================================================
# FEATURE IMPORTANCE
# =====================================================

rf_model = models[
    "Random Forest"
]

feature_importance = pd.DataFrame(
    {
        "Feature": X.columns,
        "Importance":
            rf_model.feature_importances_
    }
)

feature_importance = (
    feature_importance
    .sort_values(
        by="Importance",
        ascending=False
    )
)

print("\nFeature Importance")

print(feature_importance)

plt.figure(figsize=(8,5))

sns.barplot(
    x="Importance",
    y="Feature",
    data=feature_importance
)

plt.title(
    "Random Forest Feature Importance"
)

plt.tight_layout()

plt.show()


# =====================================================
# MODEL COMPARISON
# =====================================================

plt.figure(figsize=(8,5))

sns.barplot(
    x="Model",
    y="Accuracy",
    data=results_df
)

plt.title(
    "Model Accuracy Comparison"
)

plt.ylabel(
    "Accuracy"
)

plt.xticks(rotation=15)

plt.tight_layout()

plt.show()

# =====================================================
# CONFUSION MATRICES
# =====================================================

for name, model in models.items():

    predictions = model.predict(
        X_test
    )

    cm = confusion_matrix(
        y_test,
        predictions
    )

    plt.figure(figsize=(6,5))

    sns.heatmap(
        cm,
        annot=True,
        fmt="d",
        cmap="Blues"
    )

    plt.title(
        f"{name} Confusion Matrix"
    )

    plt.xlabel(
        "Predicted"
    )

    plt.ylabel(
        "Actual"
    )

    plt.tight_layout()

    plt.show()