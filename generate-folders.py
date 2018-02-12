import os

NUMBER_OF_WEEKS = 22

current_week = 1
target_path = os.path.dirname(os.path.abspath(__file__))

while current_week <= NUMBER_OF_WEEKS:
    dir_name = "week-{}".format(str(current_week))
    dir_path = os.path.join(target_path, dir_name)

    # also generate the subfolders
    folders = [dir_path, os.path.join(dir_path, "wcc"), os.path.join(dir_path, "pfa"), os.path.join(dir_path, "phc"), os.path.join(dir_path, "assignments")]

    # print "dir_name: {}".format(dir_name)
    for sf in folders:
        try:
            print sf
            os.mkdir(sf)
        except OSError:
            continue
    
    current_week += 1