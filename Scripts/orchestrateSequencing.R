################################################################################
#
# Set here the runtime parameters:

investigator_email <- "daniel.fischer@luke.fi"        # Leave empty if no email should be sent
mode <- "AI"
#mode <- "Expert"

################################################################################
## Internal code below

# Logical, use this for development, no sequencer runs nor AI is applied, but stored results are used.
  devel <- FALSE

# Logical, to check from where we come
  fromOrchestration <- TRUE

# Get the running index
  availableReports <- list.files(pattern = "monsterSequence_Report_*")
  if(length(availableReports)>0){
    runningIndex <- gsub("monsterSequence_Report_", "", availableReports)
    runningIndex <- gsub(".pdf", "", runningIndex)
    runningIndex <- max(as.numeric(sub("^0+", "", runningIndex)))+1
    runningIndex <- formatC(runningIndex, width = 5, format = "d", flag = "0")
  } else {
    runningIndex <- "00001"
  }
  
# Determine the new file name and render report
  rmarkdown::render('monsterSequencer.Rmd', output_file=paste0('monsterSequence_Report_',runningIndex,'.pdf'), output_format='pdf_document')

# Send out the report
  if(investigator_email!="") source("emailReport.R")
  
# Write out the sequencing information
  sequencingRun <- data.frame(date =  gsub(" ", "_", Sys.time()),
                              email = investigator_email,
                              sequencingRun = runningIndex,
                              genotypes = paste(genotypes, collapse=""))
  
  ifelse(file.exists("overview_sequencing_runs.tsv"), append <- TRUE, append <- FALSE)
  write.table(sequencingRun, file="overview_sequencing_runs.tsv", sep="\t", row.names = FALSE, quote=FALSE, append=append, col.names = !append)
  
# Now open the creted pdf also
  system(paste0('open "monsterSequence_Report_',runningIndex,'.pdf"'))
  