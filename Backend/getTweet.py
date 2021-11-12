import snscrape
import snscrape.modules.twitter as sntwitter
# Creating list to append tweet data to

def getTweet(hashtag):
    # Using TwitterSearchScraper to scrape data and append tweets to list
    for i, tweet in enumerate(sntwitter.TwitterSearchScraper('hashtag:'+hashtag).get_items()):
        # print(tweet.content + '\n\n\n\n')
        tc=tweet.content
        tc=tc.strip()
        tc=tc.replace('\n','')
        return tc
        if i > 10:
            break
        # tweets_list2.append([tweet.date, tweet.id, tweet.content, tweet.user.username])

# print(tweets_list2)



print(getTweet('arduino'))