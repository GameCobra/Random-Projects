S = 5 #Size of maze
N = 3 #Number of bananas stolen
B = 5 #Number of bananas on banana tile

exitAmount = -1

def SplitString(value : str, amount : int):
    outList = []
    for i in range(amount):
        outList.append([])
    for i in range(len(value)):
            outList[i % amount].append(value[i])
    return outList

grid = SplitString("OOEWSMGWOOMWGGOGOMWGMWOGM", S)
# OEW
# MWS
# OGO

def FindStart():
    for i in range(len(grid)):
        for j in range(len(grid)):
            if grid[i][j] == "S":
                return [i, j]

# {Bananas: , path: []}
toDo = [{"Positiion": FindStart(),"Bananas" : 0, "Path" : []}]

def GetAdjacentTiles(x : int, y : int):
    returnList = []

    if y > 0: #Up
        returnList.append([grid[x][y - 1], x, y-1])
    if x < len(grid) - 1: #Right
        returnList.append([grid[x + 1][y], x + 1, y])
    if y < len(grid) - 1: #Down
        returnList.append([grid[x][y + 1], x, y + 1])
    if x > 0: #left 
        returnList.append([grid[x - 1][y], x - 1, y])
    return returnList

def GetGoodAdjacentTiles(x : int, y : int):
    adjacentTiles = GetAdjacentTiles(x, y)
    i = 0
    while (True):
        if adjacentTiles[i][0] == "W":
            adjacentTiles.pop(i)
            i -= 1
        i += 1
        if i >= (len(adjacentTiles)):
            break
    return adjacentTiles

def execute():
    global exitAmount
    element = toDo.pop()
    adjEl = GetGoodAdjacentTiles(*element["Positiion"])
    for i in range(len(adjEl)):
        if [adjEl[i][1], adjEl[i][2]] in element["Path"]:
            continue
        path = element["Path"]
        path.append(element["Positiion"])
        if adjEl[i][0] == "G":
            toDo.append({"Positiion": [adjEl[i][1], adjEl[i][2]],"Bananas" : element["Bananas"] + B, "Path" : path})
        if adjEl[i][0] == "M":
            if element["Bananas"] - N < 0:
                continue
            toDo.append({"Positiion": [adjEl[i][1], adjEl[i][2]],"Bananas" : element["Bananas"] - N, "Path" : path})
        if adjEl[i][0] == "O":
            toDo.append({"Positiion": [adjEl[i][1], adjEl[i][2]],"Bananas" : element["Bananas"], "Path" : path})
        if adjEl[i][0] == "E":
            exitAmount = max(exitAmount, element["Bananas"])



while (len(toDo) != 0):
    execute()
print(exitAmount)