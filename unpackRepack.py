# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: step2 --conditions auto:run2_data -s RAW2DIGI,L1Reco,RECO --process reRECO -n 30 --data --eventcontent RECO --scenario HeavyIons --datatier RECO --repacked --customise Configuration/DataProcessing/RecoTLR.customiseRun2PromptHI --no_exec
import FWCore.ParameterSet.Config as cms

process = cms.Process('HLTEmulator')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContentHeavyIons_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff')
process.load('Configuration.StandardSequences.RawToDigi_Data_cff')
process.load('Configuration.StandardSequences.L1Reco_cff')
process.load('Configuration.StandardSequences.ReconstructionHeavyIons_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

# Input source
#process.source = cms.Source("PoolSource",
#    fileNames = cms.untracked.vstring('file:step2_DIGI2RAW.root'),
#    secondaryFileNames = cms.untracked.vstring()
#)
process.source = cms.Source("NewEventStreamFileReader",
        fileNames = cms.untracked.vstring(
'root://eoscms.cern.ch///store/t0streamer/Data/HIPhysicsVirginRaw/000/262/768/run262768_ls0150_streamHIPhysicsVirginRaw_StorageManager.dat', 
'root://eoscms.cern.ch///store/t0streamer/Data/HIPhysicsVirginRaw/000/262/768/run262768_ls0151_streamHIPhysicsVirginRaw_StorageManager.dat', 
'root://eoscms.cern.ch///store/t0streamer/Data/HIPhysicsVirginRaw/000/262/768/run262768_ls0152_streamHIPhysicsVirginRaw_StorageManager.dat' 
)
)

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('step2 nevts:30'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)

# Output definition

process.RECOoutput = cms.OutputModule("PoolOutputModule",
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('RAW'),
        filterName = cms.untracked.string('')
    ),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    fileName = cms.untracked.string('/data/abaty/Run2VirginRawData/temp/VR_Repacked.root'),
    #outputCommands = process.RECOEventContent.outputCommands,
    outputCommands = cms.untracked.vstring('keep *','drop *_*_*_HLT', 'drop *_*_*_LHC', 'drop SiStrip*_*_*_*','keep *_Tri*_*_HLT','drop FED*_*_*_*','keep *_rawDataRepacker_*_*','drop *_rawDataRepacker_*_HLT','drop DetIdedmEDCollection_*_*_*'),
    splitLevel = cms.untracked.int32(0)
)

# Additional output definition

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '75X_dataRun2_PromptHI_v3', '')

from RecoLocalTracker.SiStripZeroSuppression.SiStripZeroSuppression_cfi import *
process.siStripZeroSuppression.Algorithms.PedestalSubtractionFedMode = cms.bool(False)
process.siStripZeroSuppression.Algorithms.CommonModeNoiseSubtractionMode = cms.string("IteratedMedian")
process.siStripZeroSuppression.doAPVRestore = cms.bool(True)
process.siStripZeroSuppression.produceRawDigis = cms.bool(True)
process.siStripZeroSuppression.produceCalculatedBaseline = cms.bool(True)
process.siStripZeroSuppression.storeCM = cms.bool(True)
process.siStripZeroSuppression.storeInZScollBadAPV = cms.bool(True)
process.ZS = cms.Sequence(process.siStripZeroSuppression)


process.load('Configuration.StandardSequences.DigiToRaw_Repack_cff')



# Path and EndPath definitions
process.raw2digi_step = cms.Path(process.siStripDigis+process.ZS)
process.reconstruction_step = cms.Path(process.striptrackerlocalreco)
#process.reconstruction_step = cms.Path(process.striptrackerlocalreco)
process.endjob_step = cms.Path(process.endOfProcess)
process.repack = cms.Path(process.DigiToSplitRawRepack)
process.RECOoutput_step = cms.EndPath(process.RECOoutput)
#process.Timer_step = cms.Path(process.myTimer)

# Schedule definition
#process.schedule = cms.Schedule(process.raw2digi_step,process.reconstruction_step,process.hipmonitor_step, process.RECOoutput_step)
process.schedule = cms.Schedule(process.raw2digi_step, process.repack,process.RECOoutput_step)
#process.raw2digi_step = cms.Path(process.RawToDigi)
#process.L1Reco_step = cms.Path(process.L1Reco)
#process.reconstruction_step = cms.Path(process.reconstructionHeavyIons)
#process.endjob_step = cms.EndPath(process.endOfProcess)
#process.RECOoutput_step = cms.EndPath(process.RECOoutput)
#process.schedule = cms.Schedule(process.raw2digi_step,process.reconstruction_step,process.endjob_step,process.RECOoutput_step)



# Schedule definition
#process.schedule = cms.Schedule(process.raw2digi_step,process.L1Reco_step,process.reconstruction_step,process.endjob_step,process.RECOoutput_step)

process.L1RawToDigiSeq = cms.Sequence(process.gctDigis)
#process.RawToDigi_Legacy = cms.Sequence(process.csctfDigis+process.dttfDigis+process.L1RawToDigiSeq+process.gtDigis+process.siPixelDigis+process.siStripDigis+process.ecalDigis+process.ecalPreshowerDigis+process.hcalDigis+process.muonCSCDigis+process.muonDTDigis+process.muonRPCDigis+process.castorDigis+process.scalersRawToDigi+process.tcdsDigis)
#process.RawToDigiLegacyPath = cms.Path(process.RawToDigi_Legacy)
#process.schedule = cms.Schedule(process.RawToDigiLegacyPath,process.reconstruction_step,process.endjob_step,process.RECOoutput_step)








# customisation of the process.

# Automatic addition of the customisation function from Configuration.DataProcessing.RecoTLR
from Configuration.DataProcessing.RecoTLR import customiseRun2PromptHI 

#call to customisation function customiseRun2PromptHI imported from Configuration.DataProcessing.RecoTLR
process = customiseRun2PromptHI(process)

# End of customisation functions

#from Configuration.Applications.ConfigBuilder import MassReplaceInputTag
#MassReplaceInputTag(process)

