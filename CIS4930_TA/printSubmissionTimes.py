import hashlib
import time
import random
import requests
from datetime import datetime

API_KEY = "201ad2f8084cdd6fb622979946b5b2ab9a7a7723"
API_SECRET = "6cf9d555f7837e8ea52b4f6607f55f19fc26755f"
CONTEST_ID = 666222

def make_request(method, params):
    params["apiKey"] = API_KEY
    params["time"] = int(time.time())
    sorted_params = sorted(params.items())
    param_str = "&".join(f"{k}={v}" for k, v in sorted_params)
    rand = f"{random.randint(100000, 999999):06d}"
    sig_str = f"{rand}/{method}?{param_str}#{API_SECRET}"
    sig_hash = hashlib.sha512(sig_str.encode()).hexdigest()
    params["apiSig"] = rand + sig_hash
    url = f"https://codeforces.com/api/{method}"
    return requests.get(url, params=params).json()

result = make_request("contest.standings", {
    "contestId": CONTEST_ID,
    "from": 1,
    "showUnofficial": "true",
})

contest = result["result"]["contest"]
problems = result["result"]["problems"]
rows = result["result"]["rows"]
start_time = contest["startTimeSeconds"]

for row in rows:
    handle = row["party"]["members"][0]["handle"]
    if handle.lower() != "masodym605":
        continue
    
    print(f"Results for {handle}:\n")
    for i, p in enumerate(row["problemResults"]):
        prob_name = problems[i]["name"]
        rejected = p.get("rejectedAttemptCount", 0)
        
        if p["points"] > 0:
            rel_time = p.get("bestSubmissionTimeSeconds", 0)
            abs_time = start_time + rel_time
            ts = datetime.fromtimestamp(abs_time).strftime("%Y-%m-%d %H:%M:%S")
            mins = rel_time // 60
            print(f"  Problem {problems[i]['index']}: AC at {ts} ({mins} min) - {rejected} wrong attempts before")
        else:
            print(f"  Problem {problems[i]['index']}: not solved - {rejected} attempts")
