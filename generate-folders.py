import os

NUMBER_OF_WEEKS = 19

current_week = 1
target_path = os.path.dirname(os.path.abspath(__file__))

while current_week <= NUMBER_OF_WEEKS:
    dir_name = "week-{}".format(str(current_week))
    dir_path = os.path.join(target_path, dir_name)
    # print "dir_name: {}".format(dir_name)
    try:
        os.mkdir(dir_path)
    except OSError:
        pass
    current_week += 1