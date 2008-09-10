dat <- read.table("dext-0.dat",header=T)

plot(log(dat$time)~dat$noise)
plot(log(dat$time),dat$distance)
