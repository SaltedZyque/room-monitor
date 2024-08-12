# ROAM: Room Occupancy Activity Monitor

# Welcome to ROAM!

A significant issue in college facilities has been the lack of appropriate space for the student population. Due to this, users of particular rooms are unable to plan for when to visit the room to do their work or activity. ROAM uses various sensors connected to an IOT device to autonomously collect data for the purposes of measuring the room occupancy and activity status of a room and report to a user. 

This readme will provide a brief guide on how to set up the ROAM device and descriptions of files within this directory.

The repository also includes a simple presentation to showcase the product. (see `ROAM_presentation.pptx`)

## 1. Data Collection

The diagram below provides a schematic on how the hardware is setup.
Components used are as follows:
- `9V Battery`
- `ARD Mic Module 4` - for collecting audio input
- `ESP8266 NodeMCU v2` - microcontroller unit with WiFi module built-in
- `PIR Sensor HC SR501` - for motion detection
- 2x `3pin IR sensor` - detecting incomers and outgoers 

![[Components.png]]

Files related to data collection and storage are within folder `data_ROAM`:
`data_ROAM` : data collection code to be flashed into the MCU*
	* Note that API keys and credentials are not within this repository
`data_raw.csv` : raw file of readings collected from the MCU
`data.csv` : readings adjusted for analysis


## 2. Internet of Things
### 2.1 Data Analysis
Files related to data analysis are within folder `analysis_ROAM`

### 2.2 Actuation
The data is used by a discord bot to report back information to users. The bot is made on Javascript. 

Files related to the setup are within folder `discord_ROAM`
`src/index.js` : is the main Javascript file for the running of the bot
`package.json` : gives basic information about the Discord bot file 

To set up a Discord bot personally on your server, please follow the following guides
https://discordjs.guide/preparations/setting-up-a-bot-application.html
https://discordjs.guide/preparations/adding-your-bot-to-servers.html