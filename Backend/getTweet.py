import snscrape
import snscrape.modules.twitter as sntwitter
import random
# Creating list to append tweet data to
tL=[]
def getTweet(hashtag):
    global tL
    # Using TwitterSearchScraper to scrape data and append tweets to list
    for i, tweet in enumerate(sntwitter.TwitterSearchScraper('#'+hashtag).get_items()):
        # print(tweet.content + '\n\n\n\n')
        tc=tweet.content
        tc=tc.strip()
        tc=tc.replace('\n','')
        # print(tc)
        # print(tweet.date)
        return tc+';Date: '+str(tweet.date)+';Username: '+tweet.username
        # tc=tc.strip()
        # tc=tc.replace('\n','')
        # tL.append(tc)
        # if i > 80:
        #     return
        #     break
        # # tweets_list2.append([tweet.date, tweet.id, tweet.content, tweet.user.username])

# print(tweets_list2)


def getTData(hashtag):
    return getTweet(hashtag)
    
    

# print(getTData('BaseBall'))


