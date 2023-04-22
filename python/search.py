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


def carParser(car):
    words = []
    for key in car:
        if not isinstance(car[key], str):
            words.append((key + " " + str(car[key])).lower())
            continue
        words.append(car[key].lower())
    return " ".join(words[1:])


start = time.time_ns()
database = readDatabase("fakedata.json")
sentences = []
for car in database:
    sentences.append(carParser(car))
end = time.time_ns()
print(f"Nanoseconds taken : {end - start}")
print(f" {len(sentences)} Cars")
