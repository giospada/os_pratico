import os
import sys
import pdb


def export_fild(data,fild):
    for i in data.split('\n'):
        splitted = i.split(':');
        if(splitted[0]==fild):
            return splitted[1].strip()
    return None

def readStatus(dir,fileds):
    try:
        content = ''
        with open(dir+'/status') as f:
            content = f.read()
        return list(map(lambda x: export_fild(content,x),fileds))
    except Exception as e:
        return None


def main():
    uid = os.getuid()
    with os.scandir('/proc') as c_dir:
        for entry in c_dir:
            res = readStatus(entry.path,["Uid","Name","VmSize"])
            if(res==None or any(list(map(lambda x:x==None,res)))): 
                continue
            if not (str(uid) in res[0].split("\t")):
                continue
            print(f"il nome dell'eseguibile {res[1]}, e l'attuale occupazione di memoria {res[2]}")



                

    

if __name__ == "__main__":
    main()
