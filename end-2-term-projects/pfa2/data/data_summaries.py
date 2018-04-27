import pandas as pd
import numpy as np
import json, csv
import re
import os

CURRENT_DIR = os.path.dirname(os.path.realpath(__file__))
TARGET_DIR = os.path.join(CURRENT_DIR, "pop")
EXPORT_DIR = os.path.join(CURRENT_DIR, "export")

print("target directory is: {}".format(TARGET_DIR))

files_to_process = [f for f in os.listdir(TARGET_DIR) if re.match(r"\w+\.geojson", f)]

exported_columns = ["NAME", "POP_MAX", "CENTROID_LON", "CENTROID_LAT"]
exported_rows = [exported_columns]

print("files to process:\n\t{}".format("\n\t".join(files_to_process)))

# create output folder if it doesn't exist
if not os.path.exists(EXPORT_DIR):
    os.mkdir(EXPORT_DIR)

# compute population and centroid for each continent
for geojson_file in files_to_process:
    
    print("\nprocessing file: {}".format(geojson_file))
    
    try: 
        current_continent = re.findall(r"\w+_", geojson_file)[0][:-1]
        print("continent name: {}".format(current_continent))
    except IndexError:
        print("skipping!")
        print("file name must contain a _ in order to be splitted")
        continue
    
    # open current file
    with open(os.path.join(TARGET_DIR, geojson_file)) as gf:
        continent_json = json.load(gf)

    # load its geojson properties
    properties = [p["properties"] for p in continent_json["features"]]
    
    # generate the dataframe columns from the properties dictionary
    df = pd.DataFrame.from_dict(properties)
    
    print("first 5 cities:")
    print(df.head())

    total_pop_max = df["POP_MAX"].sum()

    print("total POP_MAX of continent: {}".format(total_pop_max))

    # TODO: compute the centroid of each continent
    sum_of_lon = df["LONGITUDE"].sum()
    sum_of_lat = df["LATITUDE"].sum()
    num_rows = df["LONGITUDE"].shape[0]
    length_of_lat = df["LATITUDE"].shape[0]
    centroid_lon = sum_of_lon/num_rows
    centroid_lat = sum_of_lat/num_rows
    print("continent centroid: {}".format([centroid_lon, centroid_lat]))
    print("-"*60)

    current_row = [current_continent, total_pop_max, centroid_lon, centroid_lat]
    exported_rows.append(current_row)

    # add those infos to the final dataframe that we will export

# export dataframe to csv
with open(os.path.join(EXPORT_DIR, "all_continents.csv"), "w") as ef:
    writer = csv.writer(ef)
    writer.writerows(exported_rows)
