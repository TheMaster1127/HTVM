

function print(value) {
    console.log(value)
}

// Convert value to string
function STR(value) {
    if (value === null || value === undefined) {
        return ""; // Return a string for null or undefined
    } else if (typeof value === 'number') {
        return value.toString();
    } else if (typeof value === 'boolean') {
        return value ? "1" : "0";
    } else if (typeof value === 'string') {
        return value; // Return the string as is
    } else {
        // Handle any unexpected types gracefully
        return String(value); // Convert any other type to a string
    }
}

// Function to generate a random integer between min and max (inclusive)
function Random(min, max) {
    // Generate and return a random number within the specified range
    return Math.floor(Math.random() * (max - min + 1)) + min;
}

function StrLen(s) {
    // Return the length of the given string
    return s.length;
}

function SubStr(str, startPos, length = -1) {
    let result = "";
    let strLen = str.length;
    // Handle negative starting positions (counting from the end)
    if (startPos < 0) {
        startPos = strLen + startPos;
        if (startPos < 0) startPos = 0;  // Ensure it doesn't go beyond the start of the string
    } else {
        startPos -= 1; // Convert to 0-based index for internal operations
    }
    // Handle length
    if (length < 0) {
        length = strLen - startPos; // Length to the end of the string
    } else if (startPos + length > strLen) {
        length = strLen - startPos; // Adjust length to fit within the string
    }
    // Extract the substring
    result = str.substr(startPos, length);
    return result;
}

function Mod(dividend, divisor) {
    return dividend % divisor;
}

function HTVM_Append(arr, value) {
    arr.push(value);
}

function HTVM_Size(arr) {
    return arr.length;
}


// --- Global Arrays for Sane Keyword Alternatives ---
let global_SaneIndexNames = ["A_I", "A_Current", "A_Iteration", "A_Idx", "A_Counter", "LoopIndex", "CurrentItemNo", "A_Position", "A_Num", "A_Step", "A_Seq", "A_Ordinal", "A_Rank", "A_Row", "A_Column", "A_Depth", "A_Level", "A_FilePos", "A_LineNum", "A_CharPos", "A_ItemNum", "A_RecordId", "A_NodeId", "A_ArrayIndex", "A_ListPosition", "A_MapKeyIndex", "A_ProcessCounter", "A_ThreadIndex", "A_TaskID", "A_JobID", "A_EventIndex", "A_MessageID", "A_PacketNumber", "A_FrameCounter", "A_TickCount", "A_Cycle", "A_Phase", "A_Stage", "A_Section", "A_Chapter", "A_Verse", "A_Paragraph", "A_Sentence", "A_WordIndex", "A_LetterIndex", "A_ByteOffset", "A_BlockNum", "A_SectorID", "A_ClusterRef", "A_PageIndex", "A_BufferSlot", "A_StackPointer", "A_HeapMarker", "A_RegistryKey", "A_UserID", "A_SessionCounter", "A_TransactionNum", "A_OrderID", "A_ProductID", "A_CustomerID", "A_EmployeeIndex", "A_StudentId", "A_CourseNum", "A_BookMark", "A_ReferenceId", "A_PointerVal", "A_HandleId", "A_SocketIndex", "A_PortNum", "A_ChannelId", "A_StreamPosition", "A_ResourceIndex", "A_AssetId", "A_ComponentRef", "A_EntityNum", "A_SpriteIndex", "A_TileCoord", "A_VertexId", "A_PolygonIndex", "A_PixelRow", "A_PixelCol", "A_ColorIndex", "A_PaletteRef", "A_SoundIndex", "A_MusicTrack", "A_EffectSlot", "A_ButtonId", "A_MenuIndex", "A_WindowHandle", "A_ControlId", "A_FormElementIndex", "A_DatabaseRow", "A_QueryIndex", "A_ResultOffset", "A_ReportSectionNum", "A_LogEntryId", "A_BackupVersion", "A_RevisionNum", "A_CommitCounter", "A_BranchIndex", "A_TagID", "A_VersionMarker", "idx", "i", "j", "k", "count", "counter", "iter", "loopVar", "LoopCount", "itemNum", "elementNo", "SeqNum", "RecCount", "FilePos", "TheIndex", "MyLoopIter", "ItemPointer", "CursorPosition", "StepValue", "B_Index", "C_Iter", "D_Count", "E_Pos", "F_idx", "G_i", "H_k", "I_n", "J_Counter", "K_Var", "L_LoopVar", "M_Tracker", "N_Pointer", "O_Seq", "P_Current", "Q_Num", "R_Step", "S_PosVal", "T_IterVal", "U_IndexVal", "V_LoopCounter", "W_LoopNumber", "X_ItemIndex", "Y_ElementIndex", "Z_RecordIndex", "AlphaIdx", "BetaCount", "GammaIter", "DeltaPos", "EpsilonNum", "ZetaSeq", "EtaStep", "ThetaTracker", "IotaPointer", "KappaLoopVar", "LambdaCurrent", "MuItemNum", "NuElementNo", "XiSeqNum", "OmicronRecCount", "PiFilePos", "RhoLoopCount", "SigmaIterVal", "TauIndexVal", "UpsilonCursor", "PhiStepValue", "ChiItemPointer", "PsiElementCounter", "OmegaLoopIter", "IteratorMan", "CountMaster", "IndexKing", "LoopBoss", "NumberCruncher", "PositionFinder", "StepSkipper", "SequenceSorcerer", "OrdinalOracle", "RankRanger", "RowRider", "ColumnCommander", "DepthDiver", "LevelLeaper", "FileFinger", "LineLiner", "CharChaser", "ItemInspector", "RecordRuler", "NodeNavigator", "ArrayArtist", "ListLifter", "MapMaestro", "ProcessPilot", "ThreadTamer", "TaskTrackerPrime", "JobJuggler", "EventExplorer", "MessageMover", "PacketPicker", "FrameFollower", "TickTock", "CycleChief", "PhasePhantom", "StageStomper", "SectionSeeker", "ChapterChampion", "VerseVoyager", "ParagraphPilot", "SentenceScanner", "WordWizard", "LetterLasso", "ByteBoss", "BlockBuilder", "SectorSleuth", "ClusterCrusader", "PageProwler", "BufferBuddy", "StackStalker", "HeapHero", "RegistryRanger", "UserEnumerator", "SessionScribe", "TransactionTracer", "OrderOriginator", "ProductPickerPrime", "CustomerCounter", "EmployeeEnumerator", "StudentScanner", "CourseCataloger", "BookMarkBuddy", "ReferenceRanger", "PointerPro", "HandleHolder", "SocketSelector", "PortPilot", "ChannelChallenger", "StreamSeeker", "ResourceRanger", "AssetAccountant", "ComponentCommander", "EntityEnumerator", "SpriteScanner", "TileTracker", "VertexValidator", "PolygonPilot", "PixelPusherRow", "PixelPusherCol", "ColorCoder", "PalettePicker", "SoundSelector", "MusicMaestro", "EffectEnabler", "ButtonBasher", "MenuMover", "WindowWrangler", "ControlCrusader", "FormFollower", "DatabaseDigger", "QueryQuester", "ResultRetriever", "ReportRuler", "LogLogger", "BackupBuddy", "RevisionRanger", "CommitCounterPrime", "BranchBoss", "TagTracker", "VersionValidator", "LoopDeLoop", "CountVonCount", "IndexDex", "IterNation", "StepMasterFlex"];
let global_SaneLoopFieldNames = ["A_Item", "A_FieldVal", "A_Value", "A_LoopData", "A_Element", "LoopFieldContent", "CurrentValue", "A_Content", "A_EntryData", "A_RecordData", "A_TextSegment", "A_Datum", "A_Token", "A_Word", "A_Line", "A_Character", "A_Byte", "A_Block", "A_Sector", "A_Cluster", "A_PageContent", "A_BufferData", "A_StackItem", "A_HeapObject", "A_RegistryValue", "A_UserField", "A_SessionData", "A_TransactionDetail", "A_OrderItem", "A_ProductInfo", "A_CustomerDetail", "A_EmployeeData", "A_StudentInfo", "A_CourseMaterial", "A_BookContent", "A_ReferenceValue", "A_PointerTarget", "A_HandleInfo", "A_SocketData", "A_PortInfo", "A_ChannelContent", "A_StreamData", "A_ResourceValue", "A_AssetData", "A_ComponentState", "A_EntityAttribute", "A_SpriteData", "A_TileInfo", "A_VertexValue", "A_PolygonData", "A_PixelValue", "A_ColorData", "A_PaletteEntry", "A_SoundClip", "A_MusicData", "A_EffectParam", "A_ButtonText", "A_MenuItemLabel", "A_WindowTitle", "A_ControlValue", "A_FormData", "A_DatabaseField", "A_QueryResult", "A_ReportData", "A_LogMessage", "A_BackupFileContent", "A_RevisionData", "A_CommitMessage", "A_BranchInfo", "A_TagValue", "A_VersionDetail", "item", "element", "value", "data", "field", "record", "entry", "txt", "segment", "loopItem", "CurrentData", "FieldValue", "ItemContent", "ElementInfo", "RecordEntry", "EntryDetail", "MyItem", "TheValue", "ThisData", "AnElement", "SomeField", "MyRecord", "TheEntry", "ThisText", "AContent", "CurrentFieldVal", "IteratedContent", "FetchedRecord", "ParsedData", "LoopFieldData", "DataElement", "B_Item", "C_Value", "D_Data", "E_Field", "F_Record", "G_Entry", "H_Text", "I_Content", "J_Element", "K_LoopData", "L_CurrentVal", "M_Segment", "N_Token", "O_Word", "P_Line", "Q_Datum", "R_AssetInfo", "S_ComponentData", "T_EntityVal", "U_SpriteInfo", "V_TileData", "W_VertexData", "X_PolygonInfo", "Y_PixelData", "Z_ColorValue", "AlphaItem", "BetaValue", "GammaData", "DeltaField", "EpsilonRecord", "ZetaEntry", "EtaText", "ThetaContent", "IotaElement", "KappaLoopData", "LambdaCurrentVal", "MuSegment", "NuToken", "XiWord", "OmicronLine", "PiDatum", "RhoAssetInfo", "SigmaComponentData", "TauEntityVal", "UpsilonSpriteInfo", "PhiTileData", "ChiVertexData", "PsiPolygonInfo", "OmegaPixelData", "ItemDude", "ValueGal", "DataMan", "FieldFinder", "RecordKeeper", "EntryExplorer", "TextTwister", "ContentCollector", "ElementExtractor", "LoopLoot", "CurrentCargo", "SegmentSnatcher", "TokenTaker", "WordWrangler", "LineLifter", "DatumDigger", "AssetAccessor", "ComponentCatcher", "EntityExaminer", "SpriteScannerPrime", "TileTaster", "VertexVoyager", "PolygonPicker", "PixelProfiler", "ColorCollector", "PaletteProber", "SoundSniffer", "MusicMiner", "EffectEvaluator", "ButtonLabel", "MenuItemMagician", "WindowTitleWizard", "ControlContent", "FormFiller", "DatabaseDiver", "QueryQuesterPrime", "ResultReader", "ReportRenderer", "LogLine", "BackupBlob", "RevisionReader", "CommitComment", "BranchBuddy", "TagText", "VersionValue", "TheGoods", "WhatYouGot", "CurrentStuff", "LoopOutput", "FieldOfDreams"];
let global_SaneIncrementKeywords = ["inc", "addOne", "plusUp", "incrementValue", "StepUp", "NextVal", "Advance", "IncrementBy1", "UpTick", "LevelUp", "Boost", "PlusOne", "IncVal", "GoUp", "Forward", "Proceed", "Augment", "Raise", "Elevate", "Progress", "Gain", "Accrue", "PlusIt", "OneMore", "TickForward", "AdvanceCounter", "IncrementCounter", "StepForward", "NextNumber", "ValueUp", "Bump", "NudgeUp", "IncByOne", "SumOne", "AddTo", "Grow", "Enlarge", "ExpandVal", "ScalarUp", "NumericUp", "CountUp", "IterateForward", "SequenceNext", "ProgressValue", "IncrementStep", "ForwardMarch", "PlusPlusCustom", "IncreaseAmount", "AddQuantity", "LiftValue", "HikeValue", "SurgeValue", "RiseValue", "AmplifyVal", "EscalateVal", "MountUp", "ShootUp", "SpringUp", "VaultUp", "AscendVal", "ClimbVal", "SoarVal", "SkyrocketVal", "ZenithStep", "PeakPlus", "SummitInc", "ApexAdd", "CrestCount", "PinnaclePlus", "VertexInc", "TopTick", "MaxStep", "UltraInc", "MegaPlus", "GigaAdd", "TeraCount", "HyperIncrement", "SuperStep", "PowerUp", "ChargeUp", "EnergizePlus", "ActivateInc", "TriggerNext", "FireUp", "IgnitePlus", "LaunchInc", "BlastOffAdd", "AccelerateVal", "SpeedUp", "FastForwardStep", "QuickInc", "RapidPlus", "SwiftAdd", "NimbleCount", "AgileStep", "BriskInc", "FleetPlus", "VelocityUp", "MomentumInc", "ForceAdd", "ThrustUp", "ImpulsePlus", "PropelInc", "DriveForward", "PushValue", "ShoveUp", "HeavePlus", "HoistInc", "ElevatorUp", "EscalatorPlus", "StairwayInc", "LadderAdd", "RampUp", "InclinePlus", "UpgradeVal", "EnhanceStep", "RefineInc", "OptimizePlus", "PerfectAdd", "PolishUp", "SharpenInc", "HonePlus", "TuneUp", "CalibrateInc", "AdjustPlus", "FineTuneVal", "PrecisionStep", "AccuracyInc", "DotPlus", "CrossAdd", "CheckUp", "MarkInc", "ScorePlus", "PointAdd", "TallyUp", "RegisterInc", "LogPlus", "RecordAdd", "NotateUp", "DocumentInc", "ChartPlus", "GraphAdd", "PlotUp", "MapInc", "NavigateForward", "ExploreNext", "DiscoverPlus", "UncoverInc", "RevealAdd", "ExposeUp", "ManifestInc", "MaterializePlus", "GenerateNext", "CreateInc", "ProduceAdd", "FormUp", "ShapeInc", "BuildPlus", "ConstructAdd", "FabricateUp", "AssembleInc", "ComposePlus", "DesignNext", "ArchitectInc", "EngineerAdd", "DevelopUp", "EvolveInc", "MaturePlus", "RipenAdd", "BlossomUp", "FlowerInc", "SproutPlus", "GerminateAdd", "CultivateUp", "NurtureInc", "FosterPlus", "DevelopValue", "GrowValue", "AdvanceValue", "ProgressByOne", "StepValueUp", "NextInSequence", "IncrementOperator", "PlusOperator", "AddOp", "IncOp", "LevelUpPlayer", "ScorePoint", "GainLife", "ChargeBattery", "FillTank", "RaiseVolume", "BrightenScreen", "ZoomIn", "ExpandView", "NextChapter", "NextTrack", "SkipForward", "FastForwardMedia", "IncreaseSpeed", "AdvanceTurn", "NextLevelGame", "UnlockNext", "ProceedToNext", "OneStepMore", "PlusUltraMeme", "YeetUp", "ToTheMoon", "StonksGoUp", "BigBrainInc", "GalaxyBrainPlus", "ChadStep", "SigmaGrindInc", "WojakHappyPlus", "PepeThumbsUp", "DogeMuchIncrease", "ThisIsTheWayInc", "IncrementoPatronum", "WingardiumIncreosa", "ExpectoIncrementum", "AccioNextNumber", "UpAndAdam", "RiseAndShineInc", "GoForth", "OnwardsAndUpwards", "HigherGround", "ElevateMind", "PlusPositive", "AddJoy", "IncrementHappiness", "BoostMorale", "LevelUpLife", "AdvanceWisdom", "GainExperience", "ProgressJourney", "StepIntoFuture", "NextAdventure", "ForwardMomentum", "PositiveVibesInc", "GoodTimesPlus", "MakeItBetter", "ImproveScore", "OptimizeLife", "RefineCharacter", "HoneSkills", "SharpenWit", "TuneMind", "CalibrateSoul", "AdjustAttitude"];
let global_SaneDecrementKeywords = ["dec", "subOne", "minusDown", "decrementValue", "StepDown", "PrevVal", "Retreat", "DecrementBy1", "DownTick", "LevelDown", "Nerf", "MinusOne", "DecVal", "GoDown", "Backward", "Recede", "Diminish", "Reduce", "Lower", "Regress", "Lose", "Deplete", "MinusIt", "OneLess", "TickBackward", "RetreatCounter", "DecrementCounter", "StepBackward", "PrevNumber", "ValueDown", "Drop", "NudgeDown", "DecByOne", "SubtractOne", "TakeFrom", "Shrink", "Condense", "ContractVal", "ScalarDown", "NumericDown", "CountDown", "IterateBackward", "SequencePrev", "RegressValue", "DecrementStep", "BackwardMarch", "MinusMinusCustom", "DecreaseAmount", "SubtractQuantity", "LowerValue", "DipValue", "PlungeValue", "FallValue", "DampenVal", "AttenuateVal", "SubsideDown", "SinkDown", "DescendVal", "DeclineVal", "WaneVal", "EbbVal", "NadirStep", "TroughMinus", "BottomDec", "AbyssSub", "ValleyCount", "RecessMinus", "FloorDec", "MinStep", "UltraDec", "MegaMinus", "GigaSub", "TeraCountDown", "HyperDecrement", "SuperStepDown", "PowerDown", "DrainDown", "DepleteMinus", "DeactivateDec", "TriggerPrev", "DouseDown", "ExtinguishMinus", "LandDec", "ReturnToBaseSub", "DecelerateVal", "SlowDown", "RewindStep", "QuickDec", "RapidMinus", "SwiftSub", "LethargicCount", "SluggishStep", "LazyDec", "TardyMinus", "VelocityDown", "ResistanceDec", "BrakeSub", "HaltDown", "DragMinus", "ReelInDec", "PullValueBack", "ShoveDown", "LowerItMinus", "DepressDec", "BasementDown", "SubwayMinus", "DescenderSub", "DeclineMinus", "DowngradeVal", "DiminishStep", "SimplifyDec", "StreamlineMinus", "ReduceToMin", "BluntDown", "DullMinus", "DetuneDown", "MiscalibrateDec", "ReadjustMinus", "CoarseTuneVal", "RoughStep", "ImprecisionDec", "UncheckMinus", "EraseSub", "ClearDown", "UndoDec", "RevertMinus", "ResetToPrev", "RollbackSub", "RegressToLast", "BacktrackDec", "NavigateBackward", "ReturnPrev", "ConcealMinus", "HideDec", "ObscureSub", "CoverDown", "VanishDec", "DematerializeMinus", "DegeneratePrev", "DestroyDec", "DismantleSub", "DeconstructDown", "DisassembleDec", "DecomposeMinus", "UnravelPrev", "RegressToSimple", "DevolveDec", "WitherMinus", "DecaySub", "FadeDown", "ShrinkValue", "LessenValue", "RegressValueByOne", "StepValueDown", "PrevInSequence", "DecrementOperator", "MinusOperator", "SubOp", "DecOp", "LevelDownPlayer", "LosePoint", "LoseLife", "DrainBattery", "EmptyTank", "LowerVolume", "DimScreen", "ZoomOut", "ContractView", "PrevChapter", "PrevTrack", "SkipBackward", "RewindMedia", "DecreaseSpeed", "RegressTurn", "PrevLevelGame", "LockPrev", "ReturnToPrev", "OneStepLess", "MinusUltraMeme", "YeetDown", "ToTheCore", "StonksGoDown", "SmallBrainDec", "LocalBrainMinus", "VirginStepBack", "SigmaGrindDec", "WojakSadMinus", "PepeThumbsDown", "DogeMuchDecrease", "ThisIsNotTheWayDec", "DecrementoPatronum", "WingardiumDecreosa", "ExpectoDecrementum", "AccioPrevNumber", "FallAndRest", "FadeToBlackDec", "GoBack", "DownwardsAndBackwards", "LowerGround", "SimplifyMind", "MinusNegative", "SubtractSadness", "DecrementMisery", "NerfMorale", "LevelDownLife", "RegressWisdom", "LoseExperience", "RewindJourney", "StepIntoPast", "PreviousAdventure", "BackwardMomentum", "NegativeVibesDec", "BadTimesMinus", "MakeItWorse", "WorsenScore", "ComplicateLife", "ConfuseCharacter", "DullSkills", "BluntWit", "UntuneMind", "DecalibrateSoul", "WorsenAttitude"];
let global_SaneTernary1Keywords = ["then", "ifTrue", "whenTrue", "isTrue", "trueCase", "consequent", "resultIfTrue", "outcome1", "positiveBranch", "yesPath", "affirmative", "doThis", "optionA", "firstChoice", "mainPath", "primaryResult", "directOutcome", "ifCondition", "queryThen", "checkThen", "evalTrue", "yieldTrue", "returnTrue", "getTrueVal", "trueValueIs", "TheResultIs", "PickThis", "ChooseA", "SelectIfTrue", "TrueBranchSelect", "ConditionalThen", "QueryResponse", "AskThenGive", "TruthValue", "LogicTrue", "BooleanYes", "ConfirmThen", "VerifyResult", "ValidateTrue", "IsTrueReturn", "IfYes", "ThenWhat", "Result1", "Path1", "Output1", "BranchA", "CaseTrue", "Scenario1", "PossibilityA", "Alternative1", "RouteOne", "FirstOption", "MainOutcome", "ConsequenceTrue", "PositiveResult", "TrueOutcome", "TruthPath", "AffirmativeOutcome", "DoThisPath", "ChooseThisOne", "SelectA", "TakeTrue", "TrueResultSelected", "YieldThis", "ReturnResultA", "GetValueA", "TrueExpression", "TheAnswerIs", "ThisWay", "PathYes", "BranchConfirm", "CheckMark", "ThumbsUpPath", "GoRoute", "ProceedPath", "FlowA", "StreamTrue", "ChannelYes", "PipeA", "OutputTrue", "SendTrue", "EmitYes", "ProduceA", "GenerateTrue", "CreateOptionA", "FormTrue", "ShapeResult1", "BuildBranchA", "ConstructCaseTrue", "FabricateScenario1", "AssemblePossibilityA", "ComposeAlternative1", "DesignRouteOne", "ArchitectFirstOption", "EngineerMainOutcome", "DevelopConsequenceTrue", "EvolvePositiveResult", "MatureTrueOutcome", "RipenTruthPath", "BlossomAffirmativeOutcome", "FlowerDoThisPath", "SproutChooseThisOne", "GerminateSelectA", "CultivateTakeTrue", "NurtureTrueResultSelected", "FosterYieldThis", "DevelopReturnResultA", "GrowGetValueA", "AdvanceTrueExpression", "ProgressTheAnswerIs", "StepThisWay", "NextPathYes", "ForwardBranchConfirm", "OnwardCheckMark", "HigherThumbsUpPath", "ElevateGoRoute", "LiftProceedPath", "RaiseFlowA", "AmplifyStreamTrue", "BoostChannelYes", "AugmentPipeA", "EnhanceOutputTrue", "OptimizeSendTrue", "RefineEmitYes", "SharpenProduceA", "HoneGenerateTrue", "TuneCreateOptionA", "CalibrateFormTrue", "AdjustShapeResult1", "PrecisionBuildBranchA", "AccuracyConstructCaseTrue", "ValidateFabricateScenario1", "VerifyAssemblePossibilityA", "ConfirmComposeAlternative1", "CheckDesignRouteOne", "TestArchitectFirstOption", "ProbeEngineerMainOutcome", "QueryDevelopConsequenceTrue", "AskEvolvePositiveResult", "InquireMatureTrueOutcome", "QuestionRipenTruthPath", "ExamineBlossomAffirmative", "InspectFlowerDoThisPath", "ScrutinizeSproutChooseOne", "AnalyzeGerminateSelectA", "DissectCultivateTakeTrue", "UnpackNurtureTrueResult", "DecodeFosterYieldThis", "DecipherDevelopReturnResultA", "InterpretGrowGetValueA", "UnderstandAdvanceTrueExpr", "GraspProgressTheAnswerIs", "ComprehendStepThisWay", "ApprehendNextPathYes", "PerceiveForwardBranchConf", "SenseOnwardCheckMark", "FeelHigherThumbsUpPath", "ImagineElevateGoRoute", "VisualizeLiftProceedPath", "PictureRaiseFlowA", "EnvisionAmplifyStreamTrue", "DreamBoostChannelYes", "FantasiizeAugmentPipeA", "SupposeEnhanceOutputTrue", "AssumeOptimizeSendTrue", "PresumeRefineEmitYes", "TheorizeSharpenProduceA", "HypothesizeHoneGenerateTrue", "PositTuneCreateOptionA", "PostulateCalibrateFormTrue", "ConjectureAdjustShapeResult1", "GuessPrecisionBuildBranchA", "SurmiseAccuracyConstructTrue", "InferValidateFabricateScen1", "DeduceVerifyAssemblePoss", "ReasonConfirmComposeAlt1", "LogicCheckDesignRouteOne", "CogitateTestArchitectFirst", "PonderProbeEngineerMain", "MuseQueryDevelopConsequence", "ReflectAskEvolvePositive", "MeditateInquireMatureTrue", "ContemplateQuestionRipen", "DeliberateExamineBlossom", "ConsiderInspectFlowerDo", "WeighScrutinizeSprout", "JudgeAnalyzeGerminate", "AssessDissectCultivate", "EvaluateUnpackNurture", "AppraiseDecodeFoster", "ReckonDecipherDevelop", "CalculateInterpretGrow", "ComputeUnderstandAdvance", "TallyGraspProgress", "SumComprehendStep", "TotalApprehendNext", "AggregatePerceiveForward", "SynthesizeSenseOnward", "CombineFeelHigher", "IntegrateImagineElevate", "UnifyVisualizeLift", "ConsolidatePictureRaise", "MergeEnvisionAmplify", "BlendDreamBoost", "FuseFantasiizeAugment", "JoinSupposeEnhance", "LinkAssumeOptimize", "ConnectPresumeRefine", "CoupleTheorizeSharpen", "PairHypothesizeHone", "MatchPositTune", "AlignPostulateCalibrate", "SynchronizeConjectureAdjust", "CoordinateGuessPrecision", "OrganizeSurmiseAccuracy", "StructureInferValidate", "SystematizeDeduceVerify", "ArrangeReasonConfirm", "OrderLogicCheck", "SequenceCogitateTest", "MarshalPonderProbe", "GroupMuseQuery", "CategorizeReflectAsk", "ClassifyMeditateInquire", "SortContemplateQuestion"];
let global_SaneTernary2Keywords = ["else", "ifFalse", "whenFalse", "isFalse", "falseCase", "alternative", "resultIfFalse", "outcome2", "negativeBranch", "noPath", "negative", "doThat", "optionB", "secondChoice", "alternatePath", "secondaryResult", "indirectOutcome", "elseCondition", "queryElse", "checkElse", "evalFalse", "yieldFalse", "returnFalse", "getFalseVal", "falseValueIs", "OtherwiseDo", "PickThat", "ChooseB", "SelectIfFalse", "FalseBranchSelect", "ConditionalElse", "ElseResponse", "AskThenDoOther", "FalsehoodValue", "LogicFalse", "BooleanNo", "DenyThen", "InvalidateResult", "ValidateFalse", "IsFalseReturn", "IfNo", "ElseWhat", "Result2", "Path2", "Output2", "BranchB", "CaseFalse", "Scenario2", "PossibilityB", "Alternative2", "RouteTwo", "SecondOption", "AlternateOutcome", "ConsequenceFalse", "NegativeResult", "FalseOutcome", "FalsehoodPath", "NegativeOutcome", "DoThatPath", "ChooseThatOne", "SelectB", "TakeFalse", "FalseResultSelected", "YieldThat", "ReturnResultB", "GetValueB", "FalseExpression", "TheOtherAnswer", "ThatWay", "PathNo", "BranchDeny", "CrossMark", "ThumbsDownPath", "StopRoute", "RecedePath", "FlowB", "StreamFalse", "ChannelNo", "PipeB", "OutputFalse", "SendFalse", "EmitNo", "ProduceB", "GenerateFalse", "CreateOptionB", "FormFalse", "ShapeResult2", "BuildBranchB", "ConstructCaseFalse", "FabricateScenario2", "AssemblePossibilityB", "ComposeAlternative2", "DesignRouteTwo", "ArchitectSecondOption", "EngineerAlternateOutcome", "DevelopConsequenceFalse", "EvolveNegativeResult", "MatureFalseOutcome", "RipenFalsehoodPath", "BlossomNegativeOutcome", "FlowerDoThatPath", "SproutChooseThatOne", "GerminateSelectB", "CultivateTakeFalse", "NurtureFalseResultSelect", "FosterYieldThat", "DevelopReturnResultB", "GrowGetValueB", "AdvanceFalseExpression", "ProgressTheOtherAnswer", "StepThatWay", "NextPathNo", "ForwardBranchDeny", "OnwardCrossMark", "HigherThumbsDownPath", "ElevateStopRoute", "LiftRecedePath", "RaiseFlowB", "AmplifyStreamFalse", "BoostChannelNo", "AugmentPipeB", "EnhanceOutputFalse", "OptimizeSendFalse", "RefineEmitNo", "SharpenProduceB", "HoneGenerateFalse", "TuneCreateOptionB", "CalibrateFormFalse", "AdjustShapeResult2", "PrecisionBuildBranchB", "AccuracyConstructCaseFalse", "ValidateFabricateScenario2", "VerifyAssemblePossibilityB", "ConfirmComposeAlternative2", "CheckDesignRouteTwo", "TestArchitectSecondOption", "ProbeEngineerAlternateOutcome", "QueryDevelopConsequenceFalse", "AskEvolveNegativeResult", "InquireMatureFalseOutcome", "QuestionRipenFalsehoodPath", "ExamineBlossomNegative", "InspectFlowerDoThatPath", "ScrutinizeSproutChooseThat", "AnalyzeGerminateSelectB", "DissectCultivateTakeFalse", "UnpackNurtureFalseResult", "DecodeFosterYieldThat", "DecipherDevelopReturnResB", "InterpretGrowGetValueB", "UnderstandAdvanceFalseExpr", "GraspProgressTheOtherAnswer", "ComprehendStepThatWay", "ApprehendNextPathNo", "PerceiveForwardBranchDeny", "SenseOnwardCrossMark", "FeelHigherThumbsDownPath", "ImagineElevateStopRoute", "VisualizeLiftRecedePath", "PictureRaiseFlowB", "EnvisionAmplifyStreamFalse", "DreamBoostChannelNo", "FantasiizeAugmentPipeB", "SupposeEnhanceOutputFalse", "AssumeOptimizeSendFalse", "PresumeRefineEmitNo", "TheorizeSharpenProduceB", "HypothesizeHoneGenerateFalse", "PositTuneCreateOptionB", "PostulateCalibrateFormFalse", "ConjectureAdjustShapeResult2", "GuessPrecisionBuildBranchB", "SurmiseAccuracyConstructFalse", "InferValidateFabricateScen2", "DeduceVerifyAssemblePossB", "ReasonConfirmComposeAlt2", "LogicCheckDesignRouteTwo", "CogitateTestArchitectSecond", "PonderProbeEngineerAlternate", "MuseQueryDevelopConsequenceF", "ReflectAskEvolveNegative", "MeditateInquireMatureFalse", "ContemplateQuestionRipenF", "DeliberateExamineBlossomNeg", "ConsiderInspectFlowerDoThat", "WeighScrutinizeSproutChoose", "JudgeAnalyzeGerminateSelectB", "AssessDissectCultivateTakeF", "EvaluateUnpackNurtureFalse", "AppraiseDecodeFosterYield", "ReckonDecipherDevelopReturn", "CalculateInterpretGrowValueB", "ComputeUnderstandAdvanceFalse", "TallyGraspProgressOther", "SumComprehendStepThatWay", "TotalApprehendNextPathNo", "AggregatePerceiveForwardDeny", "SynthesizeSenseOnwardCross", "CombineFeelHigherThumbsDown", "IntegrateImagineElevateStop", "UnifyVisualizeLiftRecede", "ConsolidatePictureRaiseFlowB", "MergeEnvisionAmplifyStreamF", "BlendDreamBoostChannelNo", "FuseFantasiizeAugmentPipeB", "JoinSupposeEnhanceOutputF", "LinkAssumeOptimizeSendF", "ConnectPresumeRefineEmitNo", "CoupleTheorizeSharpenProdB", "PairHypothesizeHoneGenerateF", "MatchPositTuneCreateOptionB", "AlignPostulateCalibrateFormF", "SynchronizeConjectureAdjustF", "CoordinateGuessPrecisionBuildB", "OrganizeSurmiseAccuracyConstF", "StructureInferValidateFabric2", "SystematizeDeduceVerifyAssB", "ArrangeReasonConfirmComposeA2", "OrderLogicCheckDesignRouteTwo", "SequenceCogitateTestArchSec", "MarshalPonderProbeEngineerAlt", "GroupMuseQueryDevelopConseqF", "CategorizeReflectAskEvolveN", "ClassifyMeditateInquireMatF", "SortContemplateQuestionRipenF"];
let global_SaneAssignKeywords = ["assign", "set", "is", "becomes", "equals", "letBe", "store", "defineAs", "setTo", "make", "transfer", "copyTo", "initAs", "valueIs", "varIs", "dataIs", "bindTo", "linkTo", "holdVal", "giveVal", "acceptVal", "fixVal", "placeVal", "gets", "receives", "takes"];
let global_SaneAssignAddKeywords = ["addAssign", "plusEquals", "incrementBy", "addTo", "sumAssign", "increaseBy", "accumulate", "appendNum", "augAssign", "combineAdd", "mergeSum", "growBy", "extendSum", "amassAdd", "PlusEq", "sumTo", "tallyUp"];
let global_SaneAssignConcatKeywords = ["concatAssign", "appendStr", "stringAdd", "dotEquals", "joinAssign", "textAppend", "mergeStr", "combineText", "chainStr", "linkText", "uniteStr", "fuseText", "weldStr", "CatEq", "stringJoin", "attachText"];
let global_SaneAssignSubKeywords = ["subAssign", "minusEquals", "decrementBy", "subFrom", "deductAssign", "decreaseBy", "reduceBy", "diminishBy", "shrinkBy", "lessenBy", "withdrawFrom", "MinusEq", "takeAway", "deductFrom"];
let global_SaneAssignMulKeywords = ["mulAssign", "timesEquals", "multiplyBy", "scaleBy", "productAssign", "factorAssign", "amplifyBy", "magnifyBy", "replicateBy", "TimesEq", "MultEq", "productIs"];
let global_SaneAssignDivKeywords = ["divAssign", "divideEquals", "divideBy", "ratioAssign", "quotientAssign", "shareBy", "splitBy", "partitionBy", "DivEq", "SlashEq", "quotientIs"];
let global_SaneAssignModKeywords = ["modAssign", "moduloEquals", "remainderAssign", "modBy", "cycleAssign", "wrapAssign", "ModEq", "RemEq", "PercentEq", "moduloIs"];
let global_SaneAssignShiftLeftKeywords = ["shiftLAssign", "lshEquals", "bitShiftLStore", "moveBitsLSet", "slideLStore", "LShiftEq", "LeftShiftAssign", "LSLset", "bitSlideL"];
let global_SaneAssignShiftRightKeywords = ["shiftRAssign", "rshEquals", "bitShiftRStore", "moveBitsRSet", "slideRStore", "RShiftEq", "RightShiftAssign", "RSRset", "bitSlideR"];
let global_SaneAssignUShiftRightKeywords = ["uShiftRAssign", "urshEquals", "logicShiftRStore", "zeroFillRSet", "positiveRStore", "URShiftEq", "UShiftAssign", "USRset", "logicSlideR"];
let global_SaneAssignBitAndKeywords = ["bitAndAssign", "andEquals", "maskAssign", "intersectStore", "filterAndSet", "BitAndEq", "AmpersandEq", "bitwiseAndSet"];
let global_SaneAssignBitOrKeywords = ["bitOrAssign", "orEquals", "setBitsStore", "unionOrSet", "includeOrStore", "BitOrEq", "PipeEq", "bitwiseOrSet"];
let global_SaneAssignBitXorKeywords = ["bitXorAssign", "xorEquals", "toggleBitsStore", "exclusiveOrSet", "flipBitsStore", "BitXorEq", "CaretEq", "bitwiseXorSet"];
// --- Helper Functions (Unchanged from your script, but now they use globals) ---
function GetRandomSaneIndexName() {
    return global_SaneIndexNames[Random(0, HTVM_Size(global_SaneIndexNames) - 1)];
}
function GetRandomSaneLoopFieldName() {
    return global_SaneLoopFieldNames[Random(0, HTVM_Size(global_SaneLoopFieldNames) - 1)];
}
function GetRandomSaneIncrementKeyword() {
    return global_SaneIncrementKeywords[Random(0, HTVM_Size(global_SaneIncrementKeywords) - 1)];
}
function GetRandomSaneDecrementKeyword() {
    return global_SaneDecrementKeywords[Random(0, HTVM_Size(global_SaneDecrementKeywords) - 1)];
}
function GetRandomSaneTernary1Keyword() {
    return global_SaneTernary1Keywords[Random(0, HTVM_Size(global_SaneTernary1Keywords) - 1)];
}
function GetRandomSaneTernary2Keyword() {
    return global_SaneTernary2Keywords[Random(0, HTVM_Size(global_SaneTernary2Keywords) - 1)];
}
function GetRandomSane_Assign_Keyword() {
    return global_SaneAssignKeywords[Random(0, HTVM_Size(global_SaneAssignKeywords) - 1)];
}
function GetRandomSane_AssignAdd_Keyword() {
    return global_SaneAssignAddKeywords[Random(0, HTVM_Size(global_SaneAssignAddKeywords) - 1)];
}
function GetRandomSane_AssignConcat_Keyword() {
    return global_SaneAssignConcatKeywords[Random(0, HTVM_Size(global_SaneAssignConcatKeywords) - 1)];
}
function GetRandomSane_AssignSub_Keyword() {
    return global_SaneAssignSubKeywords[Random(0, HTVM_Size(global_SaneAssignSubKeywords) - 1)];
}
function GetRandomSane_AssignMul_Keyword() {
    return global_SaneAssignMulKeywords[Random(0, HTVM_Size(global_SaneAssignMulKeywords) - 1)];
}
function GetRandomSane_AssignDiv_Keyword() {
    return global_SaneAssignDivKeywords[Random(0, HTVM_Size(global_SaneAssignDivKeywords) - 1)];
}
function GetRandomSane_AssignMod_Keyword() {
    return global_SaneAssignModKeywords[Random(0, HTVM_Size(global_SaneAssignModKeywords) - 1)];
}
function GetRandomSane_AssignShiftLeft_Keyword() {
    return global_SaneAssignShiftLeftKeywords[Random(0, HTVM_Size(global_SaneAssignShiftLeftKeywords) - 1)];
}
function GetRandomSane_AssignShiftRight_Keyword() {
    return global_SaneAssignShiftRightKeywords[Random(0, HTVM_Size(global_SaneAssignShiftRightKeywords) - 1)];
}
function GetRandomSane_AssignUShiftRight_Keyword() {
    return global_SaneAssignUShiftRightKeywords[Random(0, HTVM_Size(global_SaneAssignUShiftRightKeywords) - 1)];
}
function GetRandomSane_AssignBitAnd_Keyword() {
    return global_SaneAssignBitAndKeywords[Random(0, HTVM_Size(global_SaneAssignBitAndKeywords) - 1)];
}
function GetRandomSane_AssignBitOr_Keyword() {
    return global_SaneAssignBitOrKeywords[Random(0, HTVM_Size(global_SaneAssignBitOrKeywords) - 1)];
}
function GetRandomSane_AssignBitXor_Keyword() {
    return global_SaneAssignBitXorKeywords[Random(0, HTVM_Size(global_SaneAssignBitXorKeywords) - 1)];
}
// --- Gibberish Generation Functions (Unchanged) ---
function GenerateGibberishName(minLen, maxLen) {
    var name = "";
    var firstChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";
    var otherChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_";
    var len = Random(minLen, maxLen);
    if (len <= 0) {
        return "gib_err";
    }
    name += SubStr(firstChars, Random(1, StrLen(firstChars)), 1);
    for (let A_Index1 = 0; A_Index1 < (len - 1) + 0; A_Index1++) {
        name += SubStr(otherChars, Random(1, StrLen(otherChars)), 1);
    }
    return name;
}
function GenerateOperatorGibberishName(prefix, minTotalLen, maxTotalLen) {
    var name = prefix;
    var validChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_";
    if (minTotalLen == 1 && prefix != "") {
        if (Random(0,1) == 0) {
            return prefix;
        }
    }
    var remainingLen = Random(minTotalLen - 1, maxTotalLen - 1);
    if (prefix == "") {
        remainingLen = Random(minTotalLen, maxTotalLen);
    }
    if (prefix != "" && remainingLen <= 0) {
        remainingLen = 1;
    }
    if (prefix == "" && remainingLen < minTotalLen ) {
        remainingLen = minTotalLen;
    }
    if (remainingLen <= 0 && minTotalLen > 0) {
        remainingLen = 1;
    }
    for (let A_Index2 = 0; A_Index2 < remainingLen + 0; A_Index2++) {
        name += SubStr(validChars, Random(1, StrLen(validChars)), 1);
    }
    return name;
}
// --- Centralized Keyword Variant Generation Function ---
function GenerateKeywordVariant(defaultKeyword, saneKeywordsArray, generationMode, gibberishPrefix = "", gibberishMinLen = 2, gibberishMaxLen = 20, probDefaultMode0 = 50, probSaneOfRemainingMode0 = 60) {
    var resultKeyword;
    if (generationMode == 1) {
        resultKeyword = defaultKeyword;
    }
    else if (generationMode == 2) {
        resultKeyword = saneKeywordsArray[Random(0, HTVM_Size(saneKeywordsArray) - 1)];
    }
    else if (generationMode == 3) {
        if (gibberishPrefix != "") {
            resultKeyword = GenerateOperatorGibberishName(gibberishPrefix, gibberishMinLen, gibberishMaxLen);
        } else {
            resultKeyword = GenerateGibberishName(gibberishMinLen, gibberishMaxLen);
        }
    } else {
        var r = Random(1, 100);
        if (r <= probDefaultMode0) {
            resultKeyword = defaultKeyword;
        } else {
            if (Random(1, 100) <= probSaneOfRemainingMode0) {
                resultKeyword = saneKeywordsArray[Random(0, HTVM_Size(saneKeywordsArray) - 1)];
            } else {
                if (gibberishPrefix != "") {
                    resultKeyword = GenerateOperatorGibberishName(gibberishPrefix, gibberishMinLen, gibberishMaxLen);
                } else {
                    resultKeyword = GenerateGibberishName(gibberishMinLen, gibberishMaxLen);
                }
            }
        }
    }
    return resultKeyword;
}
// --- Refactored Main Generation Functions ---
function GenerateLoopVariableNames(generationMode = 0) {
    var indexNameFinal;
    var loopFieldNameFinal;
    let returnArray = [];
    if (generationMode == 0 && Random(1, 100) <= 10) {
        indexNameFinal = "A_Index";
        loopFieldNameFinal = "A_LoopField";
    } else {
        indexNameFinal = GenerateKeywordVariant("A_Index", global_SaneIndexNames, generationMode, "", 2, 20, 10, 78);
        loopFieldNameFinal = GenerateKeywordVariant("A_LoopField", global_SaneLoopFieldNames, generationMode, "", 2, 20, 10, 78);
    }
    HTVM_Append(returnArray, indexNameFinal);
    HTVM_Append(returnArray, loopFieldNameFinal);
    return returnArray;
}
function GenerateIncrementDecrementKeywords(generationMode = 0) {
    let returnArray = [];
    var incrementKeyword;
    var decrementKeyword;
    incrementKeyword = GenerateKeywordVariant("++", global_SaneIncrementKeywords, generationMode, "+", 2, 20, 50, 60);
    decrementKeyword = GenerateKeywordVariant("--", global_SaneDecrementKeywords, generationMode, "-", 2, 20, 50, 60);
    HTVM_Append(returnArray, incrementKeyword);
    HTVM_Append(returnArray, decrementKeyword);
    return returnArray;
}
function GenerateTernaryOperators(generationMode = 0) {
    let returnArray = [];
    var ternary1Keyword;
    var ternary2Keyword;
    ternary1Keyword = GenerateKeywordVariant("?", global_SaneTernary1Keywords, generationMode, "", 2, 20, 50, 60);
    ternary2Keyword = GenerateKeywordVariant(":", global_SaneTernary2Keywords, generationMode, "", 2, 20, 50, 60);
    HTVM_Append(returnArray, ternary1Keyword);
    HTVM_Append(returnArray, ternary2Keyword);
    return returnArray;
}
function GenerateAllAssignmentOperators(generationMode = 0) {
    let operatorKeywords = [];
    let defaults = ["=", "+=", ".=", "-=", "*=", "/=", "%=", "<<=", ">>=", ">>>=", "&=", "|=", "^="];
    let saneArrays_Names = ["global_SaneAssignKeywords", "global_SaneAssignAddKeywords", "global_SaneAssignConcatKeywords", "global_SaneAssignSubKeywords", "global_SaneAssignMulKeywords", "global_SaneAssignDivKeywords", "global_SaneAssignModKeywords", "global_SaneAssignShiftLeftKeywords", "global_SaneAssignShiftRightKeywords", "global_SaneAssignUShiftRightKeywords", "global_SaneAssignBitAndKeywords", "global_SaneAssignBitOrKeywords", "global_SaneAssignBitXorKeywords"];
    for (let A_Index3 = 0; A_Index3 < HTVM_Size(defaults) + 0; A_Index3++) {
        var currentDefault = defaults[A_Index3];
        let currentSaneArray = [];
        if (A_Index3 == 0) {
            currentSaneArray = global_SaneAssignKeywords;
        }
        else if (A_Index3 == 1) {
            currentSaneArray = global_SaneAssignAddKeywords;
        }
        else if (A_Index3 == 2) {
            currentSaneArray = global_SaneAssignConcatKeywords;
        }
        else if (A_Index3 == 3) {
            currentSaneArray = global_SaneAssignSubKeywords;
        }
        else if (A_Index3 == 4) {
            currentSaneArray = global_SaneAssignMulKeywords;
        }
        else if (A_Index3 == 5) {
            currentSaneArray = global_SaneAssignDivKeywords;
        }
        else if (A_Index3 == 6) {
            currentSaneArray = global_SaneAssignModKeywords;
        }
        else if (A_Index3 == 7) {
            currentSaneArray = global_SaneAssignShiftLeftKeywords;
        }
        else if (A_Index3 == 8) {
            currentSaneArray = global_SaneAssignShiftRightKeywords;
        }
        else if (A_Index3 == 9) {
            currentSaneArray = global_SaneAssignUShiftRightKeywords;
        }
        else if (A_Index3 == 10) {
            currentSaneArray = global_SaneAssignBitAndKeywords;
        }
        else if (A_Index3 == 11) {
            currentSaneArray = global_SaneAssignBitOrKeywords;
        }
        else if (A_Index3 == 12) {
            currentSaneArray = global_SaneAssignBitXorKeywords;
        }
        var gibMinLen = StrLen(currentDefault);
        if (gibMinLen == 0) {
            gibMinLen = 2;
        }
        HTVM_Append(operatorKeywords, GenerateKeywordVariant(currentDefault, currentSaneArray, generationMode, "", gibMinLen, 10, 50, 60));
    }
    return operatorKeywords;
}
// --- Function to generate the randomized states (UNCHANGED from your script) ---
function GenerateRandomizedStates() {
    var numStates = 13;
    let states = [];
    for (let A_Index4 = 0; A_Index4 < numStates + 0; A_Index4++) {
        HTVM_Append(states, "off");
    }
    var randomPick_c2 = Random(0, 1);
    if (randomPick_c2 == 0) {
        states[4] = "on";
        states[5] = "off";
    } else {
        states[4] = "off";
        states[5] = "on";
    }
    var randomPick_s0 = Random(0, 1);
    if (randomPick_s0 == 0) {
        states[0] = "on";
    } else {
        states[0] = "off";
    }
    if (states[0] == "on") {
        states[1] = "off";
    } else {
        var randomPick_s1 = Random(0, 1);
        if (randomPick_s1 == 0) {
            states[1] = "on";
        } else {
            states[1] = "off";
        }
    }
    if (states[0] == "on") {
        states[6] = "off";
    } else {
        var randomPick_s6 = Random(0, 1);
        if (randomPick_s6 == 0) {
            states[6] = "on";
        } else {
            states[6] = "off";
        }
    }
    let remainingIndices = [2, 3, 7, 8, 9, 10, 11, 12];
    for (let A_Index5 = 0; A_Index5 < HTVM_Size(remainingIndices) + 0; A_Index5++) {
        var currentIndexInLoop = A_Index5;
        var idxToSet = remainingIndices[currentIndexInLoop];
        var randomPick_remaining = Random(0, 1);
        if (randomPick_remaining == 0) {
            states[idxToSet] = "on";
        } else {
            states[idxToSet] = "off";
        }
    }
    return states;
}
print("--- Generating Loop Variable Name Variants (Mode Test) ---");
let loopNames = [];
print("Mode 0 (Randomized):");
loopNames = GenerateLoopVariableNames(0);
print("  IndexName = '" + loopNames[0] + "', LoopFieldName = '" + loopNames[1] + "'");
loopNames = GenerateLoopVariableNames();
print("  IndexName = '" + loopNames[0] + "', LoopFieldName = '" + loopNames[1] + "'");
print("Mode 1 (Defaults):");
loopNames = GenerateLoopVariableNames(1);
print("  IndexName = '" + loopNames[0] + "', LoopFieldName = '" + loopNames[1] + "'");
print("Mode 2 (Random Sane):");
loopNames = GenerateLoopVariableNames(2);
print("  IndexName = '" + loopNames[0] + "', LoopFieldName = '" + loopNames[1] + "'");
print("Mode 3 (Gibberish):");
loopNames = GenerateLoopVariableNames(3);
print("  IndexName = '" + loopNames[0] + "', LoopFieldName = '" + loopNames[1] + "'");
print("-------------------------------------");
print("A_Index = A_Index");
print("A_LoopField = A_LoopField");
print(";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;");
print("--- Generating Increment/Decrement Keyword Variants (Mode Test) ---");
let opKeywords = [];
print("Mode 0 (Randomized):");
opKeywords = GenerateIncrementDecrementKeywords(0);
print("  Increment = '" + opKeywords[0] + "', Decrement = '" + opKeywords[1] + "'");
opKeywords = GenerateIncrementDecrementKeywords();
print("  Increment = '" + opKeywords[0] + "', Decrement = '" + opKeywords[1] + "'");
print("Mode 1 (Defaults):");
opKeywords = GenerateIncrementDecrementKeywords(1);
print("  Increment = '" + opKeywords[0] + "', Decrement = '" + opKeywords[1] + "'");
print("Mode 2 (Random Sane):");
opKeywords = GenerateIncrementDecrementKeywords(2);
print("  Increment = '" + opKeywords[0] + "', Decrement = '" + opKeywords[1] + "'");
print("Mode 3 (Gibberish):");
opKeywords = GenerateIncrementDecrementKeywords(3);
print("  Increment = '" + opKeywords[0] + "', Decrement = '" + opKeywords[1] + "'");
print("-------------------------------------");
print("--- Generating Ternary Operator Variants (Mode Test) ---");
let ternaryOps = [];
print("Mode 0 (Randomized):");
ternaryOps = GenerateTernaryOperators(0);
print("  Op1 = '" + ternaryOps[0] + "', Op2 = '" + ternaryOps[1] + "'");
ternaryOps = GenerateTernaryOperators();
print("  Op1 = '" + ternaryOps[0] + "', Op2 = '" + ternaryOps[1] + "'");
print("Mode 1 (Defaults):");
ternaryOps = GenerateTernaryOperators(1);
print("  Op1 = '" + ternaryOps[0] + "', Op2 = '" + ternaryOps[1] + "'");
print("Mode 2 (Random Sane):");
ternaryOps = GenerateTernaryOperators(2);
print("  Op1 = '" + ternaryOps[0] + "', Op2 = '" + ternaryOps[1] + "'");
print("Mode 3 (Gibberish):");
ternaryOps = GenerateTernaryOperators(3);
print("  Op1 = '" + ternaryOps[0] + "', Op2 = '" + ternaryOps[1] + "'");
print("-------------------------------------");
print("--- Generating Assignment Operator Keyword Variants (Mode Test) ---");
let assignmentOpsGenerated = [];
let defaultOperatorSymbols = ["=", "+=", ".=", "-=", "*=", "/=", "%=", "<<=", ">>=", ">>>=", "&=", "|=", "^="];
print("Mode 0 (Randomized):");
assignmentOpsGenerated = GenerateAllAssignmentOperators(0);
for (let A_Index6 = 0; A_Index6 < HTVM_Size(assignmentOpsGenerated) + 0; A_Index6++) {
    print("  " + defaultOperatorSymbols[A_Index6] + " -> '" + assignmentOpsGenerated[A_Index6] + "'");
}
assignmentOpsGenerated = GenerateAllAssignmentOperators();
print("Mode 0 (Randomized - 2nd call):");
for (let A_Index7 = 0; A_Index7 < HTVM_Size(assignmentOpsGenerated) + 0; A_Index7++) {
    print("  " + defaultOperatorSymbols[A_Index7] + " -> '" + assignmentOpsGenerated[A_Index7] + "'");
}
print("Mode 1 (Defaults):");
assignmentOpsGenerated = GenerateAllAssignmentOperators(1);
for (let A_Index8 = 0; A_Index8 < HTVM_Size(assignmentOpsGenerated) + 0; A_Index8++) {
    print("  " + defaultOperatorSymbols[A_Index8] + " -> '" + assignmentOpsGenerated[A_Index8] + "'");
}
print("Mode 2 (Random Sane):");
assignmentOpsGenerated = GenerateAllAssignmentOperators(2);
for (let A_Index9 = 0; A_Index9 < HTVM_Size(assignmentOpsGenerated) + 0; A_Index9++) {
    print("  " + defaultOperatorSymbols[A_Index9] + " -> '" + assignmentOpsGenerated[A_Index9] + "'");
}
print("Mode 3 (Gibberish):");
assignmentOpsGenerated = GenerateAllAssignmentOperators(3);
for (let A_Index10 = 0; A_Index10 < HTVM_Size(assignmentOpsGenerated) + 0; A_Index10++) {
    print("  " + defaultOperatorSymbols[A_Index10] + " -> '" + assignmentOpsGenerated[A_Index10] + "'");
}
print("-------------------------------------");
let outArrFromStates = [];
outArrFromStates = GenerateRandomizedStates();
print("--- Output from GenerateRandomizedStates (Unchanged Function) ---");
for (let A_Index11 = 0; A_Index11 < HTVM_Size(outArrFromStates) + 0; A_Index11++) {
    print("State " + STR(A_Index11) + ": " + outArrFromStates[A_Index11]);
}
print(";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;");
