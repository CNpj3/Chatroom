import itertools, random

STARTNUM = 7

# 1-52
deck = ['0', 
		'SA','S2','S3','S4','S5','S6','S7','S8','S9','S10','SJ','SQ','SK',
		'HA','H2','H3','H4','H5','H6','H7','H8','H9','H10','HJ','HQ','HK',
		'DA','D2','D3','D4','D5','D6','D7','D8','D9','D10','DJ','DQ','DK',
		'CA','C2','C3','C4','C5','C6','C7','C8','C9','C10','CJ','CQ','CK']
colorCard = {
		'SA':1,'S2':2,'S3':3,'S4':4,'S5':5,'S6':6,'S7':7,'S8':8,'S9':9,'S10':10,'SJ':11,'SQ':12,'SK':13,
		'HA':14,'H2':15,'H3':16,'H4':17,'H5':18,'H6':19,'H7':20,'H8':21,'H9':22,'H10':23,'HJ':24,'HQ':25,'HK':26,
		'DA':27,'D2':28,'D3':29,'D4':30,'D5':31,'D6':32,'D7':33,'D8':34,'D9':35,'D10':36,'DJ':37,'DQ':38,'DK':39,
		'CA':40,'C2':41,'C3':42,'C4':43,'C5':44,'C6':45,'C7':46,'C8':47,'C9':48,'C10':49,'CJ':50,'CQ':51,'CK':52}

currentDeck = []

# make a deck of cards
# deck = list(itertools.product(range(1,14),['S','H','D','C']))
# shuffle the cards
random.shuffle(deck)

def rules():
	print("\n---------------------------------------------------")
	print("[規則解說]\n")
	print("有四種花色，依照大小排序分別是Space, Heart, Diamond, Club")
	print("每種花色各有13張，分別是A,2,3,4,5,6,7,8,9,10,J,Q,K")
	print("起始7張手牌，每次回合結束後，如果還有手牌，需要再從牌庫加抽兩張")
	print("回合期間，可以選擇出三張以上的同數字牌，且將花色由大到小排序（ex S7 H7 D7）")
	print("或是出三張以上同花色且數字接續的牌，依照A-K的順序排序（ex S3 S4 S5），注意QKA這類的順序是不合法的！")
	print("\n那麼讓我們開始吧 >< \n")
	return

def initDraw():
	handCard = []
	for i in range(STARTNUM):
		handCard.append(deck[i])
	currentDeck = deck[STARTNUM:]
	# print(', '.join(handCard))
	# print(', '.join(currentDeck))
	return handCard

def dealInputCard(userInput, handCard):
	userInput = userInput.split(' ')
	print(userInput)
    # len(
	return handCard

def draw(handCard):
	# handCard.append(currentDeck[0])
	# del currentDeck[0]
	return handCard

def playIteration(handCard):
	status = True
	turn = 1
	while (status):
		print("第",turn,"回合進行")
		print("手牌：",end='')
		print(', '.join(handCard))
		userInput = input("請出牌，如果不出牌請打pass，結束遊戲請輸入exit >>> ")
		if (userInput == 'pass'):
			continue
		elif (userInput == 'exit'):
			break
		else:
			handCard = dealInputCard(userInput, handCard)
			if (len(handCard) == 0):
				status=False
		draw(handCard)
		turn = turn + 1
	return

def play():
	print("\n發予起始手牌...")
	handCard = initDraw()
	print(', '.join(handCard))
	print()

	playIteration(handCard)
	return


# main
name = input("歡迎來到史萊姆的第一個家，請輸入你的名字 >>> ")
print("\n你好，",name, "大大")
inst = input("play(p) or help(h) >>> ")

if (inst=='h' or inst=='help'):
	rules()
elif (inst=='p' or inst=='play'):
	play()
