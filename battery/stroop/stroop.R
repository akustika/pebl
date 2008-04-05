datall <- read.table("stroop-0.txt")
colnames(datall) <- c("sub","block","trial","type","cond","shade","word","resp","corr","respnum","start","rt")

datall$resptype <- ceiling(datall$block/2)##forgot to record this.

##Just keep the correct trials and those after practice
keep <- datall$corr==1 & datall$block > 0

dat <- datall[keep,]


cond2 <- c(1,3,2,2)[dat$cond] #forgot to record this too.



x <- exp(tapply(log(dat$rt),list(cond2,dat$type,dat$resptype),mean))

xlab <- c("Consistent","One\ndimension","Inconsistent")
par(mfrow=c(1,3))
matplot(x[,,1],type="b",ylim=c(400,1600),main="Colored Word Responses",pch=c(16,18),cex=2,xaxt="n",ylab="Mean Response Time")
axis(1,1:3,xlab)
matplot(x[,,2],type="b",ylim=c(400,1600),main="Black Word Responses",pch=c(16,18),cex=2,xaxt="n",ylab="Mean Response Time")
axis(1,1:3,xlab)
matplot(x[,,3],type="b",ylim=c(400,1600),main="Colored Patch Responses",pch=c(16,18),cex=2,xaxt="n",ylab="Mean Response Time")
axis(1,1:3,xlab)
legend(1,1400,c("ID Word","ID Color"),lty=c(1,2),col=c("black","red"),pch=c(16,18),cex=2,bty="n")
