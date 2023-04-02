# Eul_Efficiency_Upon_Learning_Desktop_App v1.0

![eul](https://user-images.githubusercontent.com/85050265/226510155-9bd3ed75-3b03-45e2-a58c-3313e4a7c131.png)

A respository to record source code of Focus_Tracker made my myself using C++ on [QT platform](https://www.qt.io/) 

## How to run the application
Download the .rar file and uncompress the file.
After that,run the .exe file inside to open the application. 

## Features

### Timer
It has 30 minutes,45 minutes and 60 minutes focus options.A lofi-like music will be play during every session. At the end of each session, the details of each focus session will be recorded into SQLite database.

### Tags
There is multiple tags to be choose for each session, etc : coding,study,reading and nap . 

### View Pass Record
You can view your focus statistic for the past 3 days,7days and even open the SQlite database if you want to edit it.
The data will be display in histogram view using QTChart library.

### Interfaces

![image](https://user-images.githubusercontent.com/85050265/226509816-e5f03bbd-0a62-4f2a-a50b-e5eb729a330c.png)
<br>
Main Interface

![image](https://user-images.githubusercontent.com/85050265/226509995-4ff0cbb0-6458-446f-98b1-01ea281dd0f6.png)
<br>
Another interface to display previous focus record

![image](https://user-images.githubusercontent.com/85050265/226510050-f7bbedd8-e1ae-460e-b6f7-d7d2b6c4f7dd.png)
<br>
Database editing interface to edit sqlite database
