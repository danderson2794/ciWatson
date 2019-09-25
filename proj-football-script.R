# Clear away any previos data
rm(list=ls()) 

# Load in required libraries
library(data.table)
library(lubridate)

# Interactively choose the directory with the player files
path <- choose.dir()
files <- list.files(path,pattern="*.csv",full.names=TRUE,recursive=FALSE)

for(i in 1:length(files)){
  print(files[i])
  game <- readline(prompt="Enter game: ")
  name <- readline(prompt="Enter player name: ")
  velocity_data <- fread(files[i], skip = 3, sep=",")[,20]
  naIndices <- which(is.na(velocity_data))
  velocity <- as.numeric(unlist(velocity_data[!naIndices]))*2.23694 #conversion from meters per second to mph
  time_data <- strptime(unlist((fread(files[i], skip = 3, sep=",")[!naIndices,1])), "%H:%M:%OS")
  time <- as.numeric(difftime(time_data,time_data[1],units = "secs"))
  plot(time,velocity, main = paste(game, ' ', name), xlab = "Time (sec)", ylab = "Velocity (mph)")
  results <- cbind(time,velocity)
  write.csv(results,file = paste(game,name,'Catapult Velocity Data.csv'))
}