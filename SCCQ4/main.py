S = 3 #Size of maze
N = 3 #Number of bananas stolen
B = 5 #Number of bananas on banana tile

def SplitString(value : str, amount : int):
    outList = []
    for i in range(amount):
        outList.append([])
    for i in range(len(value)):
            outList[i % amount].append(value[i])
    return outList

grid = SplitString("OEWMWSOGO", S)
# OEW
# MWS
# OGO

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

adjacentTiles = GetAdjacentTiles(2, 1)
i = 0
while (True):
    if adjacentTiles[i][0] == "W":
        adjacentTiles.pop(i)
        i -= 1
    i += 1
    if i >= (len(adjacentTiles)):
        break



print(adjacentTiles)