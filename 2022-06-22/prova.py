import os
import subprocess 
import sys

def main():
    hmap = dict()
    with os.scandir(sys.argv[1]) as dir:
        for entry in dir:
            proc=subprocess.Popen(["file",entry.path],stdout=subprocess.PIPE)
            out= proc.communicate()[0].decode("utf-8")
            if(out and len(out)!=0):
                s = out.split(':')
                s1 = s[1].strip()
                s0 = s[0].strip()
                if s1 in hmap.keys():
                    hmap[s1].append(s0)
                else:
                    hmap.update({s1:[s0]})





    for key in hmap.keys():
        print(key,":",','.join(hmap[key]))
    
if __name__ == "__main__":
    main()
