import random
import requests
import json
import os
import time



 
#Reference Lists, not changed

global heroList
global FullHeroList

def howManyAboveAverage(aList):
    #print(aList)
    average = sum(aList)/float(len(aList))
    #print(average)
    count = 0
    for item in aList:
        if item >= average:
            count += 1
    return count
    

#Creates the data to be feed into the decision trees
#Only uses data from the radient team






def getDTData(match, test):
    global heroList
    global FullHeroList
    global ItemLookUp
    '''
    g = open('DTDataLabels'+test+'.txt', 'a')
    g.write(str(match["radiant_win"]))
    asdfghjkl
    g.write("\n")
    g.close()
    '''
    f = open('DTData'+test+'.txt', 'a')
    f.write(str(match["radiant_win"]))
    
    #Puts in what heroes were used by the radient side
    rHeroes = []
    for i in range(0, len(match["players"])):
        if match["players"][i]["player_slot"] < 128:
            rHeroes.append(match["players"][i]["hero_id"])
    #I have no idea why I used str on a constant. I was probably really tired
    for i in range(len(heroList)):
        if heroList[i] in rHeroes:
            f.write("," + str(1))
        else:
            f.write("," + str(0))
    
    #adds the match duration
    f.write("," + str(match["duration"]))
    '''  
    if match["duration"] < 600:#10
        f.write("," + str(0))
    elif match["duration"] < 1500:#25
        f.write("," + str(1))
    elif match["duration"] < 2100:#35
        f.write("," + str(2))
    elif match["duration"] < 2700:#45
        f.write("," + str(3))
    elif match["duration"] < 3600:#60
        f.write("," + str(4))
    else:
        f.write("," + str(5))
        '''
    #Adds the number of players with above average gold
    goldSpent = []
    for i in range(0, len(match["players"])):
        if match["players"][i]["player_slot"] < 128:
            goldSpent.append(match["players"][i]["gold_spent"])
    f.write("," + str(howManyAboveAverage(goldSpent)))
    #print(goldSpent,howManyAboveAverage(goldSpent))
    #raise
    
    #Adds the number of players with above average levels
    level = []
    for i in range(0, len(match["players"])):
        if match["players"][i]["player_slot"] < 128:
            level.append(match["players"][i]["level"])
    f.write("," + str(howManyAboveAverage(level)))
    
    #Adds the number of players with above average kill count
    kills = []
    for i in range(0, len(match["players"])):
        if match["players"][i]["player_slot"] < 128:
            kills.append(match["players"][i]["kills"])
    f.write("," + str(howManyAboveAverage(kills)))
    
    #Adds the number of players with above average death count
    deaths = []
    for i in range(0, len(match["players"])):
        if match["players"][i]["player_slot"] < 128:
            deaths.append(match["players"][i]["deaths"])
    f.write("," + str(howManyAboveAverage(deaths)))
    
    '''
    assists = []
    for i in range(0, len(match["players"])):
        if match["players"][i]["player_slot"] < 128:
            assists.append(match["players"][i]["assists"])
    f.write("," + str(howManyAboveAverage(assists)))
    '''
    
    #Adds the number of players with above average last hits (moba thing)
    last_hits = []
    for i in range(0, len(match["players"])):
        if match["players"][i]["player_slot"] < 128:
            last_hits.append(match["players"][i]["last_hits"])
    f.write("," + str(howManyAboveAverage(last_hits)))
    
    #Adds the number of players with above average damage done to heros
    hero_damage = []
    for i in range(0, len(match["players"])):
        if match["players"][i]["player_slot"] < 128:
            hero_damage.append(match["players"][i]["hero_damage"])
    f.write("," + str(howManyAboveAverage(hero_damage)))
    
    #Adds the number of players with above average damage done to towers
    tower_damage = []
    for i in range(0, len(match["players"])):
        if match["players"][i]["player_slot"] < 128:
            tower_damage.append(match["players"][i]["tower_damage"])
    f.write("," + str(howManyAboveAverage(tower_damage)))
    
    #Adds the number of players with above average total item values
    #'''
    PlayersItemList = []
    for i in range(len(match["players"])):
        playerItem = []
        for j in range(5):
            if match["players"][i]["player_slot"] < 128:
                if not match["players"][i]["item_"+str(j)] == 0:
                    playerItem.append(ItemLookUp[match["players"][i]["item_"+str(j)]])
        if len(playerItem) > 0:
            PlayersItemList.append(sum(playerItem)/float(len(playerItem)))
        elif match["players"][i]["player_slot"] < 128:
            PlayersItemList.append(0)
    PlayersItemList = sorted(PlayersItemList, reverse=True)
    for item in PlayersItemList:
        f.write("," + str(item))
    
    f.write("," + str(howManyAboveAverage(PlayersItemList)))
    #'''
    
    f.write("\n")
    f.close()
        
#Creates headers for the data set made by getDTData() 
def HeadDTData(test):
    global heroList
    global heroLookUp
    f = open('DTData'+test+'.txt', 'a')
    f.write("radiant_win")
    
    for i in range(len(heroList)):
        f.write("," + str(heroLookUp[heroList[i]]))
    f.write("," + "Duration")
    f.write("," + "AboveAverGoldSpent")
    f.write("," + "AboveAverLevel")
    f.write("," + "AboveAverKills")
    f.write("," + "AboveAverDeaths")
    #f.write("," + "AboveAverAssists")
    f.write("," + "AboveAverLast_hits")
    f.write("," + "AboveAverHero_damage")
    f.write("," + "AboveAverTower_damage")
    #'''
    f.write("," + "Highest1AverageItemCost")
    f.write("," + "Highest2AverageItemCost")
    f.write("," + "Highest3AverageItemCost")
    f.write("," + "Highest4AverageItemCost")
    f.write("," + "Highest5AverageItemCost")
    f.write("," + "AboveAverItemCost")
    #'''
    f.write("\n")
    f.close()
    
    
#Creates headers for the data set for use with the apriori algorithm

def HeadHeroAData(test):
    global heroList
    f = open('HeroAData'+test+'.txt', 'a')
    g = open('HeroADataNamed'+test+'.txt', 'a')
    
    
    f.write("radiant_win")
    g.write("radiant_win")
    
    for i in range(len(FullHeroList.json()["result"]["heroes"])):
        f.write("," + str(FullHeroList.json()["result"]["heroes"][i]["name"]))
        g.write("," + str(FullHeroList.json()["result"]["heroes"][i]["name"]))
            
    f.write("\n")
    g.write("\n")
    f.close()
    g.close()
        
#Creates data set (just radient) for use with the apriori algorithm
def getHeroAData1(match, test):
    global heroList
    f = open('HeroAData'+test+'.txt', 'a')
    g = open('HeroADataNamed'+test+'.txt', 'a')
    
    
    f.write(str(match["radiant_win"]))
    g.write(str(match["radiant_win"]))
    
    rHeroes = []
    for i in range(0, len(match["players"])):
        if match["players"][i]["player_slot"] < 128:
            rHeroes.append(match["players"][i]["hero_id"])
    for i in range(len(heroList)):
        if FullHeroList.json()["result"]["heroes"][i]["id"] in rHeroes:
            f.write("," + str("one"))
            g.write("," + str("one"))
        else:
            f.write("," + str("zero"))
            g.write("," + str("zero"))
            
    f.write("\n")
    g.write("\n")
    f.close()
    g.close()
#Creates data set for use with the apriori algorithm
def getHeroAData(match, test):
    global heroList
    f = open('HeroAData'+test+'.txt', 'a')
    g = open('HeroADataNamed'+test+'.txt', 'a')
    #f.write(str(match["radiant_win"]))
    #g.write(str(match["radiant_win"]))
    
    for i in range(1, len(match["players"])):
        if match["players"][i]["player_slot"] < 128:
            if not (match["players"][i]["hero_id"]) == 0:
                f.write("," + str(match["players"][i]["hero_id"]))
                g.write("," + str(heroList[match["players"][i]["hero_id"]]))
    f.write("\n")
    g.write("\n")
    f.close()
    g.close()
    
#Saves to file item to item id key

def getItemAData(match, test):
    f = open('ItemAData'+test+'.txt', 'a')
    for i in range(len(match["players"])):
        
        if not (match["players"][i]["item_0"]) == 0:
            f.write(str(match["players"][i]["item_0"]))
        else:
            for j in range(1,6):
                if not (match["players"][i]["item_"+str(j)]) == 0:
                    f.write("," + str(match["players"][i]["item_"+str(j)]))
                    break
        for j in range(6):
            if not (match["players"][i]["item_"+str(j)]) == 0:
                f.write("," + str(match["players"][i]["item_"+str(j)]))
        f.write("\n")
    f.close()
    
#Creates refrence list for heroes and items

def MakeHeroList():
    global heroList
    global FullHeroList
    global heroLookUp
    global FullItemList
    global ItemLookUp
    #if not 'FullHeroList' in globals():
    f = open('heroList.txt', 'r')
    y = f.read()
    FullHeroList = json.loads(y)
    f.close()
    tempHeroList = [14, 44, 104, 35, 93, 8, 74, 2, 32, 9]#, 6, 1, 18, 4, 42, 71, 62, 26, 17, 41, 70, 54, 98, 34, 5, 16, 28, ]
    heroList = tempHeroList#{}
    '''
    heroList = []
    for i in range(len(FullHeroList["result"]["heroes"])):
        heroList.append(FullHeroList["result"]["heroes"][i]["id"])
    '''
    heroLookUp = {}
    for i in range(len(FullHeroList["result"]["heroes"])):
        if FullHeroList["result"]["heroes"][i]["id"] in heroList:
            heroLookUp[FullHeroList["result"]["heroes"][i]["id"]] = FullHeroList["result"]["heroes"][i]["name"]
        
    f = open('itemList.txt', 'r')
    y = f.read()
    FullItemList = json.loads(y)
    f.close()
    ItemLookUp = {}
    for i in range(len(FullItemList["result"]["items"])):
        ItemLookUp[FullItemList["result"]["items"][i]["id"]] = FullItemList["result"]["items"][i]["cost"]
        
    
#Main function

def formDataFiles(ContinueSeq = True):
    #ContinueSeq is continue from last game seen in a run
    global startSeq
    
    ContinueSeq = True
    
    url = "http://api.steampowered.com/"+"IDOTA2Match_570/"
    url = url +"GetMatchHistory/V001/"+"?"+"key=Steam Api Key"
    x = requests.get(url)
    if not ContinueSeq or not 'startSeq' in globals():
        startSeq = x.json()["result"]["matches"][0]["match_seq_num"]

    #global numberOfMatches
    numberOfMatches = 0
    notTourMatches = 0 #Stands for not useable matches (wrong game mode [dota's api doesn't actually work])
    matchIDSeen = {}
    os.chdir("Insert the working directory")
    place = 0
    '''
    f = open('ItemAData'+'.txt', 'w')
    f.close()
    f = open('ItemAData'+"Test"+'.txt', 'w')
    f.close()
    f = open('HeroAData'+'.txt', 'w')
    f.close()
    f = open('HeroAData'+"Test"+'.txt', 'w')
    f.close()
    f = open('HeroADataNamed'+'.txt', 'w')
    f.close()
    f = open('HeroADataNamed'+"Test"+'.txt', 'w')
    f.close()
    '''
    f = open('DTData'+'.txt', 'w')
    f.close()
    f = open('DTData'+"Test"+'.txt', 'w')
    f.close()
    MakeHeroList()
    #HeadHeroAData("")
    #HeadHeroAData("Test")
    HeadDTData("")
    HeadDTData("Test")
    
    url = "http://api.steampowered.com/"+"IDOTA2Match_570/"
    url = url +"GetMatchHistoryBySequenceNum/V001/"+"?"+"key=Steam Api Key"
    url = url + "&" + "start_at_match_seq_num="+str(startSeq)#2442435995"
    matchList = requests.get(url)
    while numberOfMatches < 7000:
        match = matchList.json()['result']['matches'][place]
        #print(match['match_seq_num'], match['start_time'], matchIDSeen)
        if match['match_seq_num'] in matchIDSeen or match['start_time']<1476489600: raise #Not seen before and not from current patch
        matchIDSeen[ match['match_seq_num'] ] = match['match_seq_num']
        #add to data if game mode is useable
        if ( match["game_mode"] == 1 or match["game_mode"] == 2 or match["game_mode"] == 3 or match["game_mode"] == 16 or match["game_mode"] == 22):
            chance = random.randint(1,20)
            test = ""
            if chance <= 5: test = "Test" #randomly add matches to test set
            getDTData(match, test)
            #getHeroAData(match, test)
            #getItemAData(match, test)
            numberOfMatches = numberOfMatches + 1
        else:
            notTourMatches = notTourMatches + 1
            print(match["game_mode"])
        
        #if out of games from current call, get new list of matches
        place = place + 1
        if place == len(matchList.json()['result']['matches']):
            place = 1
            url = "http://api.steampowered.com/"+"IDOTA2Match_570/"
            url = url +"GetMatchHistoryBySequenceNum/V001/"+"?"+"key=Steam Api Key"
            url = url + "&" + "start_at_match_seq_num="+str(matchList.json()['result']['matches'][len(matchList.json()['result']['matches'])-1]['match_seq_num'])
            matchList = requests.get(url)
            #time.sleep(5)
        print(numberOfMatches, place, notTourMatches)
    if ContinueSeq:
        startSeq = matchList.json()['result']['matches'][place]['match_seq_num']
formDataFiles()
#formDataFiles(False)