import pandas as pd
import re
import math

def parse_coordinates(row):
    coordinates = re.findall(r"((\-|)\d+\.*\d+)|(\d+)", row)
    coordinates = [a[0] for a in coordinates]
    return coordinates

def gudermannian(x):
    return 2 * math.atan(math.exp(x)) - math.pi / 2

def inv_gudermannian(y):
    return math.log(math.tan((y + math.pi / 2) / 2))

def mercator(coords):
    
    lon = float(coords[0])
    lat = float(coords[1])
    zoom = 0.5

    lat_rad = lat * math.pi / 180.0
    # "map-centric" latitude, in radians:
    lat_rad = inv_gudermannian(lat_rad)

    x = 2**zoom * (lon + 180.0) / 360.0
    y = 2**zoom * (math.pi - lat_rad) / (2 * math.pi)

    return float(x), float(y)

df = pd.read_csv("fusion-landing-points.csv")

df["coordinates"] = df["coordinates"].apply(parse_coordinates)

df["clean-coordinates"] = df["coordinates"]
df["xy-coordinates"] = df["clean-coordinates"].apply(mercator)

# print(df.head()[["clean-coordinates", "xy-coordinates"]])

exported_df = pd.DataFrame(df["xy-coordinates"].values.tolist())

exported_df = exported_df.rename(columns={'0': 'x', '1': 'y'})

exported_df.columns = ["x", "y"]
exported_df.index.names = ["index"]
print(exported_df.head())

# exported_df = df["xy-coordinates"]
exported_df.to_csv("fusion-cables-cartesian.csv", sep=",")