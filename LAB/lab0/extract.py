from typing import List, Sequence
from bs4 import BeautifulSoup
import subprocess
import bs4
import requests

URL = "https://www.geeksforgeeks.org/essential-linuxunix-commands/"

cmd_file = open("geek.sh", "w")

resp = requests.get(URL)
if resp.status_code != 200:
    print("failed to read website")
    exit(1)

soup = BeautifulSoup(resp.content, features="html.parser") 
tables: List[bs4.element.Tag] = list(soup.findAll("table"))

def extract_commands(table: bs4.element.Tag) -> List[str]:
    rows: List[bs4.element.Tag] = list(table.findAll("tr"))[1:]
    cmds =  list(map(lambda x: x.findAll("td")[-1].find("span").get_text(), rows))
    return cmds


cmds: List[str] = []
for table in tables[:-1]:
    cmds.extend(list(map(lambda x: x + "\n", extract_commands(table))))
    
print(f"total commands : {len(cmds)}")
cmd_file.writelines(cmds)
