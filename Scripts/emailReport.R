# This script sends out the MonsterReport
library("mailR")  # This is only required if you plan to send out reports

receiver <- investigator_email
if(!fromOrchestration) receiver <- "daniel.fischer@luke.fi"

tmp <- read.table("emailCredentials.tsv", sep="\t")
emailaddress <- tmp[1,2]
username <- tmp[2,2]
password <- tmp[3,2]
smtpserver <- tmp[4,2]

bodyText <- "
Dear Monster Investigator! \n
Your sequencing run was completed successfully and a Monster was identified!
Attached you find the called genotypes and the predicted appearances, based on the 
called variants. 

As discoverer, please feel free to name the Monster, if you would like to enter the
monster into the Monster Database, please answer to this email and just type the
assign name into the body.

Best regards on behalf of the Luke Bioinformatics Method Support Team,
 Daniel

For further information on the used technology, please visit \n
https://github.com/fischuu/Lego-Sequencer \n
http://danielfischer.name/life/tech-projects/lego-sequencer/
"

send.mail(from = emailaddress,
          to = receiver,
          subject = "Monster sequencing run finished",
          body = bodyText,
          smtp = list(host.name = smtpserver, port = 25,
                      user.name = username,
                      passwd = password, ssl = TRUE),
          authenticate = TRUE,
          send = TRUE,
          attach.files = paste0('monsterSequence_Report_',runningIndex,'.pdf'))
