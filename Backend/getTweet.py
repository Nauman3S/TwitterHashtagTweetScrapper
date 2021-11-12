import snscrape
import snscrape.modules.twitter as sntwitter
import random
# Creating list to append tweet data to
tL=[]
def getTweet(hashtag):
    global tL
    # Using TwitterSearchScraper to scrape data and append tweets to list
    for i, tweet in enumerate(sntwitter.TwitterSearchScraper('hashtag:'+hashtag).get_items()):
        # print(tweet.content + '\n\n\n\n')
        tc=tweet.content
        tc=tc.strip()
        tc=tc.replace('\n','')
        tL.append(tc)
        if i > 80:
            return
            break
        # tweets_list2.append([tweet.date, tweet.id, tweet.content, tweet.user.username])

# print(tweets_list2)

print()
def getTData(hashtag):
    getTweet(hashtag)
    g=random.randint(0,len(tL))
    return tL[g]

# print(getTData('arduino'))


