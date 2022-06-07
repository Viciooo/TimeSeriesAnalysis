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
This program is now incorporated inside [this notebook](./src/main/analysis_of_time_series_from_web_scraping.ipynb). So all you need to do is follow the instructions below to run it and it will guide you step by step on how to run this program.
### Python used for:

- analysing time series
- predicting the data trends

#### How to setup your enviroment?
- Go to [this link](https://www.anaconda.com/products/distribution) and download Anaconda Scientific Distribution of Python3
- Install it following [these instructions](https://docs.anaconda.com/anaconda/install/)
- Change your location to where the project with .yml file is
- Type `conda env create -f tsa_course_env.yml` and press Enter
- Wait for a bit
- Now your Python Scientific environment is ready &mdash; type `jupyter notebook` to start your data science journey

## Sources:
- https://towardsdatascience.com/the-complete-guide-to-time-series-analysis-and-forecasting-70d476bfe775
- https://www.tableau.com/learn/articles/time-series-analysis#:~:text=What%20is%20time%20series%20analysis,data%20points%20intermittently%20or%20randomly.
- https://www.udemy.com/course/python-for-time-series-data-analysis/
