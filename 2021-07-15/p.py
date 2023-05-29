
import sys
import os


def update(minmax, new):
    if new[0][0] < minmax[0][0]:
        minmax[0] = new[0]
    if new[1][0] > minmax[1][0]:
        minmax[1] = new[1]
    return minmax

def goDown(dir):
    minmax = [(sys.float_info.max,"NULL"),(sys.float_info.min,"NULL")]
    if os.path.isdir(dir):
        with os.scandir(dir) as c_dir:
            for entry in c_dir:
                file = entry.path
                minmax=update(goDown(file),minmax)
    elif os.path.isfile(dir):
        # get the modify time
        time=os.stat(dir).st_mtime
        return [(time,dir),(time,dir)]

    return minmax




def main():
    dir = sys.argv[1]
    a=goDown(dir)
    print(f'min: {a[0][1]}')
    print(f'max: {a[1][1]}')

if __name__ == "__main__":
    main()