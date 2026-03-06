import hashlib
import time
import random
import requests

# === FILL THESE IN ===
API_KEY = "201ad2f8084cdd6fb622979946b5b2ab9a7a7723"
API_SECRET = "6cf9d555f7837e8ea52b4f6607f55f19fc26755f"
CONTEST_ID = 664874 # CP0
# =====================

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
    resp = requests.get(url, params=params)
    return resp.json()

roster = {
    "Alex42006": "Alex Milanes",
    "AlexanderBernich": "Alexander Bernich",
    "CarlosHERNANDEZ": "Carlos Hernandez",
    "LukeGorman": "Luke Gorman",
    "Serralq": "Alexander Dao",
    "Tiger9406": "Tiger Cao",
    "ZachFisher": "Zachary Fisher",
    "beutelm": "Matthew Beutel",
    "cibarbia05": "Christian Ibarbia Ruiz",
    "daviddorante": "David Dorante",
    "hari_patell": "Hari-Krishna Patel",
    "jordanprice": "Jordan Price",
    "kkonuru": "Kausthubh Konuru",
    "lucasrodr1010": "Lucas Rodriguez",
    "sbalkhi": "Syed Balkhi",
    "sprinkuls": "May Macler",
    "steve3rom": "Steve Sajeev",
    "storple": "Matthew Nguyen",
    "ttavera234": "Thomas Tavera",
    "vinlin03": "Vincent Lin",
    "wangjustin": "Justin Wang",
    "zhang.hanlin": "Hanlin Zhang",
    "zhue2026": "Ethan Zhu",
    "1dom": "Dominic Ghizzoni",
    "AtinaRu": "Atina Ruvinova",
    "CameronSilverman": "Cameron Silverman",
    "DeclanM": "Declan McKoen",
    "JHogan24": "Jacob Hogan",
    "Jnissan": "Jacob Nissan",
    "Matthew_DErrico": "Matthew DErrico",
    "Nicholas_Thyssen": "Nicholas Thyssen",
    "PKscorpion": "Peyton Kromash",
    "Rmryan": "Russell Ryan",
    "RyanBrito920": "Ryan Brito",
    "RyanMachado": "Ryan Machado",
    "shashank0703": "Shashank Gutta",
    "ThomasZh": "Thomas Zhao",
    "Tsarnas03": "Tyler Tsarnas",
    "Warphi": "Jack Gordon",
    "YoungBeef": "Aaron Young",
    "Zacarywebb": "Zacary Webb",
    "alexanderlou": "Alexander Lou",
    "andrewchuangsaladin": "Andrew Chuang Saladin",
    "bakarikerr": "Bakari Kerr",
    "brianborrego": "Brian Borrego",
    "christianbeta": "Christian Betancourt Dias",
    "danielelbaz7": "Daniel Elbaz",
    "dustinnguyenUF": "Dustin Nguyen",
    "ebaucom21": "Elijah Baucom",
    "ethanelliott": "Ethan Elliott",
    "ezhu": "Eric Zhu",
    "gatorj": "Jason Li",
    "helenzou": "Helen Zou",
    "jbeckmann1": "Jason Beckmann",
    "jebron": "Jehan Peralta",
    "kimchae": "Alexander Kim",
    "masodym605": "Mustafa Masody",
    "mjmilez": "Matthew Miles",
    "parsh89": "Parsh Patel",
    "pgz": "Phoenix Gutierrez",
    "ramidarwiche": "Rami Darwiche",
    "seamush": "Seamus Hinz",
    "sezgow": "Joshua Roberts",
    "stonejack": "Jack Stone",
    "tchava": "Tomas Chavarria",
    "treepher": "Taran Ramu",
    "tylerlocnguyen": "Tyler Nguyen"
}

result = make_request("contest.standings", {
    "contestId": CONTEST_ID,
    "from": 1,
    "showUnofficial": "true",
})

if result.get("status") != "OK":
    print(f"API Error: {result.get('comment', result)}")
    exit(1)
contest = result["result"]["contest"]
rows = result["result"]["rows"]
num_problems = len(result["result"]["problems"])
contest_end = contest["startTimeSeconds"] + contest["durationSeconds"]
INT_MAX = 2147483647

# Case-insensitive handle lookup
roster_lower = {h.lower(): h for h in roster}

students = {}
for row in rows:
    handle_raw = row["party"]["members"][0]["handle"]
    handle = roster_lower.get(handle_raw.lower())
    if not handle:
        continue
    ptype = row["party"]["participantType"]

    if handle not in students:
        students[handle] = {"contest": 0, "contest_problems": set(), "total_problems": set(), "note": ""}

    # Track which problems were solved (by index)
    for i, p in enumerate(row["problemResults"]):
        if p["points"] > 0:
            # For CONTESTANT, also check valid submission time (not INT_MAX)
            if ptype == "CONTESTANT":
                if p.get("bestSubmissionTimeSeconds", INT_MAX) < INT_MAX:
                    students[handle]["contest_problems"].add(i)
                    students[handle]["total_problems"].add(i)
            else:
                # PRACTICE/VIRTUAL - just check points
                students[handle]["total_problems"].add(i)

# Convert sets to counts
for handle, data in students.items():
    data["contest"] = len(data["contest_problems"])
    data["total"] = len(data["total_problems"])

for handle in roster:
    if handle not in students:
        students[handle] = {"contest": 0, "total": 0, "note": "missing"}

# Calculate score based on rules
def calc_score(contest, total):
    if contest == 2:
        return 150  # both in contest
    elif contest == 1 and total == 2:
        return 120  # one in contest, other virtual/practice
    elif contest == 0 and total == 2:
        return 100  # both via other means
    elif total == 1:
        return 50   # one solved (any means)
    else:
        return 0    # none

# Output
print(f"=== {contest['name']} ===\n")

all_students = [(h, d) for h, d in students.items()]
def name_sort_key(item):
    handle, data = item
    name = roster[handle]
    parts = name.split()
    last = parts[-1] if parts else ""
    first = parts[0] if parts else ""
    return (last.lower(), first.lower())

all_students.sort(key=name_sort_key)

max_name = max(len(roster[h]) for h, _ in all_students)
max_handle = max(len(h) for h, _ in all_students)
for handle, data in all_students:
    name = roster[handle]
    score = calc_score(data["contest"], data["total"])

    # Build info string
    parts = []
    parts.append(f"{data['contest']}/{num_problems} contest, {data['total']}/{num_problems} total")
    if data["note"]:
        parts.append(data["note"])
    info = ", ".join(parts)

    print(f"  {name:<{max_name}}  {handle:<{max_handle}}  {score:>3}  ({info})")
