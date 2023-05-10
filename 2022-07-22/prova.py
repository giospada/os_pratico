import os
import sys
#import subprocess
import pdb


def main():
    dir = sys.argv[1]
    if os.path.isdir(dir):
        with os.scandir(dir) as c_dir:
            for entry in c_dir:
                file = entry.path
                if ((not os.access(file, os.X_OK)) or (not entry.is_file())):
                    continue
                temp = False
                with open(entry) as c:
                    temp = c.read(4) == [0x70, 'E', 'L', 'F']

                if temp:
                    print(file)


if __name__ == "__main__":
    main()
