# MOwNiT & C++ Project

## Topic: Time Series Analysis

### C++ used for:

- web scraping
- preparing the data
- choosing the data to process

#### How to use
##### Prerequisites
The program uses [libcurl](https://curl.se/libcurl/).  
Follow the instructions [here](https://curl.se/docs/install.html) to install it.  
Check the paths to the installed libraries in [Makefile](./src/web-scraping/Makefile) and correct them if necessary. Otherwise, the program won't compile.

##### Running and compiling
First, compile the program by typing in a terminal:
```makefile
make compile
```

Then, run it with the following command:
```makefile
make run
```

Finally, if you want to remove unnecessary files after the program execution, type:
```makefile
make clean
```
### Python used for:

- analysing time series
- predicting the data trends

## Sources:
- https://towardsdatascience.com/the-complete-guide-to-time-series-analysis-and-forecasting-70d476bfe775
- https://www.tableau.com/learn/articles/time-series-analysis#:~:text=What%20is%20time%20series%20analysis,data%20points%20intermittently%20or%20randomly.
- https://www.udemy.com/course/python-for-time-series-data-analysis/