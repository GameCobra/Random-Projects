import random
f = open("Text.txt", "r")
text = f.read()
text = text.replace("â€”", "' ")

maping = [["a", "\u0430"], ["c", "\u0441"], ["d", "\u0501"], ["e", "\u0435"], ["h", "\u04bb"], ["j", "\u0458"], ["l", "\u04cf"], ["n", "\u0578"], ["o", "\u043e"], ["p", "\u0440"], ["x", "\u0445"], ["y", "\u0443"]]

newText = ""

for i in range(len(text)):

    newText = newText + "\u200b" * 3 #0 width space

    r = random.randint(0, 4) # escape charecter
    if r == 0:
        newText = newText + "\u001b"

    r = random.randint(0, 4) # bell charecter
    if r == 0:
        newText = newText + "\u0007"
    

    r = random.randint(0, 4) # device controle charecter 1
    if r == 0:
        newText = newText + "\u0011"

    r = random.randint(0, 4) # device controle charecter 2
    if r == 0:
        newText = newText + "\u0012"


    r = random.randint(0, 4) # device controle charecter 3
    if r == 0:
        newText = newText + "\u0013"

        
    r = random.randint(0, 4) # device controle charecter 4
    if r == 0:
        newText = newText + "\u0014"


    #r = random.randint(0, 4) # nul charecter
    #if r == 0:
    #    newText = newText + "\u0000"



    newText = newText + text[i]

    for j in range(len(maping)):
        if text[i] == maping[j][0]:
            newText = newText[:-1] + maping[j][1]
    



f = open("NewText", "w", encoding="utf-8")
f.write(newText)
f.close()

