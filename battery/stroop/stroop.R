datall <- read.table("stroop-0.txt")
colnames(datall) <- c("sub","block","trial","type","cresp","cond","cond2","shade","word","resp","corr","respnum","start","rt")


datall$testtype <- ceiling(datall$block/2)

##Just keep the correct trials and those after practice
keep <- datall$corr==1 & datall$block > 0

dat <- datall[keep,]



x <- exp(tapply(log(dat$rt),list(dat$cond2,dat$type,dat$testtype),mean))


ord <- c(1,3,2)
xlab <- c("Congruent","Incongruent","One\ndimension")
par(mfrow=c(1,3))
matplot(x[ord,,1],type="b",ylim=c(400,1600),main="Colored Word Responses",pch=c(16,18),cex=2,xaxt="n",ylab="Mean Response Time")
axis(1,1:3,xlab[ord])
matplot(x[ord,,2],type="b",ylim=c(400,1600),main="Black Word Responses",pch=c(16,18),cex=2,xaxt="n",ylab="Mean Response Time")
axis(1,1:3,xlab[ord])
matplot(x[ord,,3],type="b",ylim=c(400,1600),main="Colored Patch Responses",pch=c(16,18),cex=2,xaxt="n",ylab="Mean Response Time")
axis(1,1:3,xlab[ord])
legend(1,1400,c("ID Word","ID Color"),lty=c(1,2),col=c("black","red"),pch=c(16,18),cex=2,bty="n")




ord <- c(1,3,2)
xlab <- c("Congruent","Incongruent","One\ndimension")
par(mfrow=c(1,2))
matplot(x[ord,1,],type="b",ylim=c(400,1600),main="Color Reading",pch=c(16,18),cex=2,xaxt="n",ylab="Mean Response Time")
axis(1,1:3,xlab[ord])
matplot(x[ord,2,],type="b",ylim=c(400,1600),main="Color ID",pch=c(16,18),cex=2,xaxt="n",ylab="Mean Response Time")
axis(1,1:3,xlab[ord])
legend(1,1400,c("ID Word","ID Color"),lty=c(1,2),col=c("black","red"),pch=c(16,18),cex=2,bty="n")
