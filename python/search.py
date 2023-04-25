import json
import time


def readDatabase(file_path):
    with open(file_path, "r") as f:
        data = json.load(f)
        if isinstance(data, dict):
            return [data]
        elif isinstance(data, list):
            return data
        else:
            raise ValueError(
                "Databse file must contain a JSON object or an array of JSON objects"
            )


def make_sentence(car):
    values = []
    for key, value in car.items():
        if isinstance(value, str):
            values.append(value.lower())
        elif isinstance(value, bool) and value:
            key = key.lower().replace("_", " ")
            values.append(key)
        elif isinstance(value, (int, float)):
            key = key.lower().replace("_", " ")
            values.append(f"{key} {value}")
    if len(values) >= 2:
        return " ".join(values)
    else:
        return "Could not generate sentence: missing make or model info"


start = time.time_ns()
database = readDatabase("fakedata.json")
sentences = []
for car in database:
    sentences.append(make_sentence(car))
end = time.time_ns()
print(f"Nanoseconds taken : {end - start}")
print(f" {len(sentences)} Cars")
