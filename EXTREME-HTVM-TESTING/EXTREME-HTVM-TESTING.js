

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


// Function to generate the randomized states (from previous request, UNCHANGED)
function GenerateRandomizedStates() {
    var numStates = 13;
    let states = [];
    for (let A_Index1 = 0; A_Index1 < numStates + 0; A_Index1++) {
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
    for (let A_Index2 = 0; A_Index2 < HTVM_Size(remainingIndices) + 0; A_Index2++) {
        var currentIndexInLoop = A_Index2;
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
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
// Start of A_Index / A_LoopField variant generation
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
// Function to generate a random "sane" name for A_Index alternatives (UNCHANGED HELPER)
function GetRandomSaneIndexName() {
    let saneNames = ["A_I", "A_Current", "A_Iteration", "A_Idx", "A_Counter", "LoopIndex", "CurrentItemNo", "A_Position", "A_Num", "A_Step", "A_Seq", "A_Ordinal", "A_Rank", "A_Row", "A_Column", "A_Depth", "A_Level", "A_FilePos", "A_LineNum", "A_CharPos", "A_ItemNum", "A_RecordId", "A_NodeId", "A_ArrayIndex", "A_ListPosition", "A_MapKeyIndex", "A_ProcessCounter", "A_ThreadIndex", "A_TaskID", "A_JobID", "A_EventIndex", "A_MessageID", "A_PacketNumber", "A_FrameCounter", "A_TickCount", "A_Cycle", "A_Phase", "A_Stage", "A_Section", "A_Chapter", "A_Verse", "A_Paragraph", "A_Sentence", "A_WordIndex", "A_LetterIndex", "A_ByteOffset", "A_BlockNum", "A_SectorID", "A_ClusterRef", "A_PageIndex", "A_BufferSlot", "A_StackPointer", "A_HeapMarker", "A_RegistryKey", "A_UserID", "A_SessionCounter", "A_TransactionNum", "A_OrderID", "A_ProductID", "A_CustomerID", "A_EmployeeIndex", "A_StudentId", "A_CourseNum", "A_BookMark", "A_ReferenceId", "A_PointerVal", "A_HandleId", "A_SocketIndex", "A_PortNum", "A_ChannelId", "A_StreamPosition", "A_ResourceIndex", "A_AssetId", "A_ComponentRef", "A_EntityNum", "A_SpriteIndex", "A_TileCoord", "A_VertexId", "A_PolygonIndex", "A_PixelRow", "A_PixelCol", "A_ColorIndex", "A_PaletteRef", "A_SoundIndex", "A_MusicTrack", "A_EffectSlot", "A_ButtonId", "A_MenuIndex", "A_WindowHandle", "A_ControlId", "A_FormElementIndex", "A_DatabaseRow", "A_QueryIndex", "A_ResultOffset", "A_ReportSectionNum", "A_LogEntryId", "A_BackupVersion", "A_RevisionNum", "A_CommitCounter", "A_BranchIndex", "A_TagID", "A_VersionMarker", "idx", "i", "j", "k", "count", "counter", "iter", "loopVar", "LoopCount", "itemNum", "elementNo", "SeqNum", "RecCount", "FilePos", "TheIndex", "MyLoopIter", "ItemPointer", "CursorPosition", "StepValue", "B_Index", "C_Iter", "D_Count", "E_Pos", "F_idx", "G_i", "H_k", "I_n", "J_Counter", "K_Var", "L_LoopVar", "M_Tracker", "N_Pointer", "O_Seq", "P_Current", "Q_Num", "R_Step", "S_PosVal", "T_IterVal", "U_IndexVal", "V_LoopCounter", "W_LoopNumber", "X_ItemIndex", "Y_ElementIndex", "Z_RecordIndex", "AlphaIdx", "BetaCount", "GammaIter", "DeltaPos", "EpsilonNum", "ZetaSeq", "EtaStep", "ThetaTracker", "IotaPointer", "KappaLoopVar", "LambdaCurrent", "MuItemNum", "NuElementNo", "XiSeqNum", "OmicronRecCount", "PiFilePos", "RhoLoopCount", "SigmaIterVal", "TauIndexVal", "UpsilonCursor", "PhiStepValue", "ChiItemPointer", "PsiElementCounter", "OmegaLoopIter", "IteratorMan", "CountMaster", "IndexKing", "LoopBoss", "NumberCruncher", "PositionFinder", "StepSkipper", "SequenceSorcerer", "OrdinalOracle", "RankRanger", "RowRider", "ColumnCommander", "DepthDiver", "LevelLeaper", "FileFinger", "LineLiner", "CharChaser", "ItemInspector", "RecordRuler", "NodeNavigator", "ArrayArtist", "ListLifter", "MapMaestro", "ProcessPilot", "ThreadTamer", "TaskTrackerPrime", "JobJuggler", "EventExplorer", "MessageMover", "PacketPicker", "FrameFollower", "TickTock", "CycleChief", "PhasePhantom", "StageStomper", "SectionSeeker", "ChapterChampion", "VerseVoyager", "ParagraphPilot", "SentenceScanner", "WordWizard", "LetterLasso", "ByteBoss", "BlockBuilder", "SectorSleuth", "ClusterCrusader", "PageProwler", "BufferBuddy", "StackStalker", "HeapHero", "RegistryRanger", "UserEnumerator", "SessionScribe", "TransactionTracer", "OrderOriginator", "ProductPickerPrime", "CustomerCounter", "EmployeeEnumerator", "StudentScanner", "CourseCataloger", "BookMarkBuddy", "ReferenceRanger", "PointerPro", "HandleHolder", "SocketSelector", "PortPilot", "ChannelChallenger", "StreamSeeker", "ResourceRanger", "AssetAccountant", "ComponentCommander", "EntityEnumerator", "SpriteScanner", "TileTracker", "VertexValidator", "PolygonPilot", "PixelPusherRow", "PixelPusherCol", "ColorCoder", "PalettePicker", "SoundSelector", "MusicMaestro", "EffectEnabler", "ButtonBasher", "MenuMover", "WindowWrangler", "ControlCrusader", "FormFollower", "DatabaseDigger", "QueryQuester", "ResultRetriever", "ReportRuler", "LogLogger", "BackupBuddy", "RevisionRanger", "CommitCounterPrime", "BranchBoss", "TagTracker", "VersionValidator", "LoopDeLoop", "CountVonCount", "IndexDex", "IterNation", "StepMasterFlex"];
    var randomIndex = Random(0, HTVM_Size(saneNames) - 1);
    return saneNames[randomIndex];
}
// Function to generate a random "sane" name for A_LoopField alternatives (UNCHANGED HELPER)
function GetRandomSaneLoopFieldName() {
    let saneNames = ["A_Item", "A_FieldVal", "A_Value", "A_LoopData", "A_Element", "LoopFieldContent", "CurrentValue", "A_Content", "A_EntryData", "A_RecordData", "A_TextSegment", "A_Datum", "A_Token", "A_Word", "A_Line", "A_Character", "A_Byte", "A_Block", "A_Sector", "A_Cluster", "A_PageContent", "A_BufferData", "A_StackItem", "A_HeapObject", "A_RegistryValue", "A_UserField", "A_SessionData", "A_TransactionDetail", "A_OrderItem", "A_ProductInfo", "A_CustomerDetail", "A_EmployeeData", "A_StudentInfo", "A_CourseMaterial", "A_BookContent", "A_ReferenceValue", "A_PointerTarget", "A_HandleInfo", "A_SocketData", "A_PortInfo", "A_ChannelContent", "A_StreamData", "A_ResourceValue", "A_AssetData", "A_ComponentState", "A_EntityAttribute", "A_SpriteData", "A_TileInfo", "A_VertexValue", "A_PolygonData", "A_PixelValue", "A_ColorData", "A_PaletteEntry", "A_SoundClip", "A_MusicData", "A_EffectParam", "A_ButtonText", "A_MenuItemLabel", "A_WindowTitle", "A_ControlValue", "A_FormData", "A_DatabaseField", "A_QueryResult", "A_ReportData", "A_LogMessage", "A_BackupFileContent", "A_RevisionData", "A_CommitMessage", "A_BranchInfo", "A_TagValue", "A_VersionDetail", "item", "element", "value", "data", "field", "record", "entry", "txt", "segment", "loopItem", "CurrentData", "FieldValue", "ItemContent", "ElementInfo", "RecordEntry", "EntryDetail", "MyItem", "TheValue", "ThisData", "AnElement", "SomeField", "MyRecord", "TheEntry", "ThisText", "AContent", "CurrentFieldVal", "IteratedContent", "FetchedRecord", "ParsedData", "LoopFieldData", "DataElement", "B_Item", "C_Value", "D_Data", "E_Field", "F_Record", "G_Entry", "H_Text", "I_Content", "J_Element", "K_LoopData", "L_CurrentVal", "M_Segment", "N_Token", "O_Word", "P_Line", "Q_Datum", "R_AssetInfo", "S_ComponentData", "T_EntityVal", "U_SpriteInfo", "V_TileData", "W_VertexData", "X_PolygonInfo", "Y_PixelData", "Z_ColorValue", "AlphaItem", "BetaValue", "GammaData", "DeltaField", "EpsilonRecord", "ZetaEntry", "EtaText", "ThetaContent", "IotaElement", "KappaLoopData", "LambdaCurrentVal", "MuSegment", "NuToken", "XiWord", "OmicronLine", "PiDatum", "RhoAssetInfo", "SigmaComponentData", "TauEntityVal", "UpsilonSpriteInfo", "PhiTileData", "ChiVertexData", "PsiPolygonInfo", "OmegaPixelData", "ItemDude", "ValueGal", "DataMan", "FieldFinder", "RecordKeeper", "EntryExplorer", "TextTwister", "ContentCollector", "ElementExtractor", "LoopLoot", "CurrentCargo", "SegmentSnatcher", "TokenTaker", "WordWrangler", "LineLifter", "DatumDigger", "AssetAccessor", "ComponentCatcher", "EntityExaminer", "SpriteScannerPrime", "TileTaster", "VertexVoyager", "PolygonPicker", "PixelProfiler", "ColorCollector", "PaletteProber", "SoundSniffer", "MusicMiner", "EffectEvaluator", "ButtonLabel", "MenuItemMagician", "WindowTitleWizard", "ControlContent", "FormFiller", "DatabaseDiver", "QueryQuesterPrime", "ResultReader", "ReportRenderer", "LogLine", "BackupBlob", "RevisionReader", "CommitComment", "BranchBuddy", "TagText", "VersionValue", "TheGoods", "WhatYouGot", "CurrentStuff", "LoopOutput", "FieldOfDreams"];
    var randomIndex = Random(0, HTVM_Size(saneNames) - 1);
    return saneNames[randomIndex];
}
// Function to generate a gibberish, but valid, variable name (general purpose) (UNCHANGED HELPER)
function GenerateGibberishName(minLen, maxLen) {
    var name = "";
    var firstChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";
    var otherChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_";
    var len = Random(minLen, maxLen);
    if (len <= 0) {
        return "gib_err";
    }
    name += SubStr(firstChars, Random(1, StrLen(firstChars)), 1);
    for (let A_Index3 = 0; A_Index3 < (len - 1) + 0; A_Index3++) {
        name += SubStr(otherChars, Random(1, StrLen(otherChars)), 1);
    }
    return name;
}
// UPDATED function to generate A_Index and A_LoopField variants with mode control
function GenerateLoopVariableNames(generationMode = 0) {
    var indexNameFinal;
    var loopFieldNameFinal;
    let returnArray = [];
    if (generationMode == 1) {
        indexNameFinal = "A_Index";
        loopFieldNameFinal = "A_LoopField";
    }
    else if (generationMode == 2) {
        indexNameFinal = GetRandomSaneIndexName();
        loopFieldNameFinal = GetRandomSaneLoopFieldName();
    }
    else if (generationMode == 3) {
        indexNameFinal = GenerateGibberishName(2, 20);
        loopFieldNameFinal = GenerateGibberishName(2, 20);
    } else {
        if (Random(1, 100) <= 10) {
            indexNameFinal = "A_Index";
            loopFieldNameFinal = "A_LoopField";
            HTVM_Append(returnArray, indexNameFinal);
            HTVM_Append(returnArray, loopFieldNameFinal);
            return returnArray;
        }
        if (Random(1, 100) <= 10) {
            indexNameFinal = "A_Index";
        } else {
            if (Random(1, 100) <= 20) {
                indexNameFinal = GenerateGibberishName(2, 20);
            } else {
                indexNameFinal = GetRandomSaneIndexName();
            }
        }
        if (Random(1, 100) <= 10) {
            loopFieldNameFinal = "A_LoopField";
        } else {
            if (Random(1, 100) <= 20) {
                loopFieldNameFinal = GenerateGibberishName(2, 20);
            } else {
                loopFieldNameFinal = GetRandomSaneLoopFieldName();
            }
        }
    }
    HTVM_Append(returnArray, indexNameFinal);
    HTVM_Append(returnArray, loopFieldNameFinal);
    return returnArray;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
// Start of Increment/Decrement Keyword Generation
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
// Function to generate a random "sane" increment keyword (UNCHANGED HELPER)
function GetRandomSaneIncrementKeyword() {
    let saneNames = ["inc", "addOne", "plusUp", "incrementValue", "StepUp", "NextVal", "Advance", "IncrementBy1", "UpTick", "LevelUp", "Boost", "PlusOne", "IncVal", "GoUp", "Forward", "Proceed", "Augment", "Raise", "Elevate", "Progress", "Gain", "Accrue", "PlusIt", "OneMore", "TickForward", "AdvanceCounter", "IncrementCounter", "StepForward", "NextNumber", "ValueUp", "Bump", "NudgeUp", "IncByOne", "SumOne", "AddTo", "Grow", "Enlarge", "ExpandVal", "ScalarUp", "NumericUp", "CountUp", "IterateForward", "SequenceNext", "ProgressValue", "IncrementStep", "ForwardMarch", "PlusPlusCustom", "IncreaseAmount", "AddQuantity", "LiftValue", "HikeValue", "SurgeValue", "RiseValue", "AmplifyVal", "EscalateVal", "MountUp", "ShootUp", "SpringUp", "VaultUp", "AscendVal", "ClimbVal", "SoarVal", "SkyrocketVal", "ZenithStep", "PeakPlus", "SummitInc", "ApexAdd", "CrestCount", "PinnaclePlus", "VertexInc", "TopTick", "MaxStep", "UltraInc", "MegaPlus", "GigaAdd", "TeraCount", "HyperIncrement", "SuperStep", "PowerUp", "ChargeUp", "EnergizePlus", "ActivateInc", "TriggerNext", "FireUp", "IgnitePlus", "LaunchInc", "BlastOffAdd", "AccelerateVal", "SpeedUp", "FastForwardStep", "QuickInc", "RapidPlus", "SwiftAdd", "NimbleCount", "AgileStep", "BriskInc", "FleetPlus", "VelocityUp", "MomentumInc", "ForceAdd", "ThrustUp", "ImpulsePlus", "PropelInc", "DriveForward", "PushValue", "ShoveUp", "HeavePlus", "HoistInc", "ElevatorUp", "EscalatorPlus", "StairwayInc", "LadderAdd", "RampUp", "InclinePlus", "UpgradeVal", "EnhanceStep", "RefineInc", "OptimizePlus", "PerfectAdd", "PolishUp", "SharpenInc", "HonePlus", "TuneUp", "CalibrateInc", "AdjustPlus", "FineTuneVal", "PrecisionStep", "AccuracyInc", "DotPlus", "CrossAdd", "CheckUp", "MarkInc", "ScorePlus", "PointAdd", "TallyUp", "RegisterInc", "LogPlus", "RecordAdd", "NotateUp", "DocumentInc", "ChartPlus", "GraphAdd", "PlotUp", "MapInc", "NavigateForward", "ExploreNext", "DiscoverPlus", "UncoverInc", "RevealAdd", "ExposeUp", "ManifestInc", "MaterializePlus", "GenerateNext", "CreateInc", "ProduceAdd", "FormUp", "ShapeInc", "BuildPlus", "ConstructAdd", "FabricateUp", "AssembleInc", "ComposePlus", "DesignNext", "ArchitectInc", "EngineerAdd", "DevelopUp", "EvolveInc", "MaturePlus", "RipenAdd", "BlossomUp", "FlowerInc", "SproutPlus", "GerminateAdd", "CultivateUp", "NurtureInc", "FosterPlus", "DevelopValue", "GrowValue", "AdvanceValue", "ProgressByOne", "StepValueUp", "NextInSequence", "IncrementOperator", "PlusOperator", "AddOp", "IncOp", "LevelUpPlayer", "ScorePoint", "GainLife", "ChargeBattery", "FillTank", "RaiseVolume", "BrightenScreen", "ZoomIn", "ExpandView", "NextChapter", "NextTrack", "SkipForward", "FastForwardMedia", "IncreaseSpeed", "AdvanceTurn", "NextLevelGame", "UnlockNext", "ProceedToNext", "OneStepMore", "PlusUltraMeme", "YeetUp", "ToTheMoon", "StonksGoUp", "BigBrainInc", "GalaxyBrainPlus", "ChadStep", "SigmaGrindInc", "WojakHappyPlus", "PepeThumbsUp", "DogeMuchIncrease", "ThisIsTheWayInc", "IncrementoPatronum", "WingardiumIncreosa", "ExpectoIncrementum", "AccioNextNumber", "UpAndAdam", "RiseAndShineInc", "GoForth", "OnwardsAndUpwards", "HigherGround", "ElevateMind", "PlusPositive", "AddJoy", "IncrementHappiness", "BoostMorale", "LevelUpLife", "AdvanceWisdom", "GainExperience", "ProgressJourney", "StepIntoFuture", "NextAdventure", "ForwardMomentum", "PositiveVibesInc", "GoodTimesPlus", "MakeItBetter", "ImproveScore", "OptimizeLife", "RefineCharacter", "HoneSkills", "SharpenWit", "TuneMind", "CalibrateSoul", "AdjustAttitude"];
    var randomIndex = Random(0, HTVM_Size(saneNames) - 1);
    return saneNames[randomIndex];
}
// Function to generate a random "sane" decrement keyword (UNCHANGED HELPER)
function GetRandomSaneDecrementKeyword() {
    let saneNames = ["dec", "subOne", "minusDown", "decrementValue", "StepDown", "PrevVal", "Retreat", "DecrementBy1", "DownTick", "LevelDown", "Nerf", "MinusOne", "DecVal", "GoDown", "Backward", "Recede", "Diminish", "Reduce", "Lower", "Regress", "Lose", "Deplete", "MinusIt", "OneLess", "TickBackward", "RetreatCounter", "DecrementCounter", "StepBackward", "PrevNumber", "ValueDown", "Drop", "NudgeDown", "DecByOne", "SubtractOne", "TakeFrom", "Shrink", "Condense", "ContractVal", "ScalarDown", "NumericDown", "CountDown", "IterateBackward", "SequencePrev", "RegressValue", "DecrementStep", "BackwardMarch", "MinusMinusCustom", "DecreaseAmount", "SubtractQuantity", "LowerValue", "DipValue", "PlungeValue", "FallValue", "DampenVal", "AttenuateVal", "SubsideDown", "SinkDown", "DescendVal", "DeclineVal", "WaneVal", "EbbVal", "NadirStep", "TroughMinus", "BottomDec", "AbyssSub", "ValleyCount", "RecessMinus", "FloorDec", "MinStep", "UltraDec", "MegaMinus", "GigaSub", "TeraCountDown", "HyperDecrement", "SuperStepDown", "PowerDown", "DrainDown", "DepleteMinus", "DeactivateDec", "TriggerPrev", "DouseDown", "ExtinguishMinus", "LandDec", "ReturnToBaseSub", "DecelerateVal", "SlowDown", "RewindStep", "QuickDec", "RapidMinus", "SwiftSub", "LethargicCount", "SluggishStep", "LazyDec", "TardyMinus", "VelocityDown", "ResistanceDec", "BrakeSub", "HaltDown", "DragMinus", "ReelInDec", "PullValueBack", "ShoveDown", "LowerItMinus", "DepressDec", "BasementDown", "SubwayMinus", "DescenderSub", "DeclineMinus", "DowngradeVal", "DiminishStep", "SimplifyDec", "StreamlineMinus", "ReduceToMin", "BluntDown", "DullMinus", "DetuneDown", "MiscalibrateDec", "ReadjustMinus", "CoarseTuneVal", "RoughStep", "ImprecisionDec", "UncheckMinus", "EraseSub", "ClearDown", "UndoDec", "RevertMinus", "ResetToPrev", "RollbackSub", "RegressToLast", "BacktrackDec", "NavigateBackward", "ReturnPrev", "ConcealMinus", "HideDec", "ObscureSub", "CoverDown", "VanishDec", "DematerializeMinus", "DegeneratePrev", "DestroyDec", "DismantleSub", "DeconstructDown", "DisassembleDec", "DecomposeMinus", "UnravelPrev", "RegressToSimple", "DevolveDec", "WitherMinus", "DecaySub", "FadeDown", "ShrinkValue", "LessenValue", "RegressValueByOne", "StepValueDown", "PrevInSequence", "DecrementOperator", "MinusOperator", "SubOp", "DecOp", "LevelDownPlayer", "LosePoint", "LoseLife", "DrainBattery", "EmptyTank", "LowerVolume", "DimScreen", "ZoomOut", "ContractView", "PrevChapter", "PrevTrack", "SkipBackward", "RewindMedia", "DecreaseSpeed", "RegressTurn", "PrevLevelGame", "LockPrev", "ReturnToPrev", "OneStepLess", "MinusUltraMeme", "YeetDown", "ToTheCore", "StonksGoDown", "SmallBrainDec", "LocalBrainMinus", "VirginStepBack", "SigmaGrindDec", "WojakSadMinus", "PepeThumbsDown", "DogeMuchDecrease", "ThisIsNotTheWayDec", "DecrementoPatronum", "WingardiumDecreosa", "ExpectoDecrementum", "AccioPrevNumber", "FallAndRest", "FadeToBlackDec", "GoBack", "DownwardsAndBackwards", "LowerGround", "SimplifyMind", "MinusNegative", "SubtractSadness", "DecrementMisery", "NerfMorale", "LevelDownLife", "RegressWisdom", "LoseExperience", "RewindJourney", "StepIntoPast", "PreviousAdventure", "BackwardMomentum", "NegativeVibesDec", "BadTimesMinus", "MakeItWorse", "WorsenScore", "ComplicateLife", "ConfuseCharacter", "DullSkills", "BluntWit", "UntuneMind", "DecalibrateSoul", "WorsenAttitude"];
    var randomIndex = Random(0, HTVM_Size(saneNames) - 1);
    return saneNames[randomIndex];
}
// Function to generate operator-like gibberish (e.g., "+abc", "-xyz123") (UNCHANGED HELPER)
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
    for (let A_Index4 = 0; A_Index4 < remainingLen + 0; A_Index4++) {
        name += SubStr(validChars, Random(1, StrLen(validChars)), 1);
    }
    return name;
}
// UPDATED function to generate Increment and Decrement keywords with mode control
function GenerateIncrementDecrementKeywords(generationMode = 0) {
    var incrementKeyword;
    var decrementKeyword;
    let returnArray = [];
    if (generationMode == 1) {
        incrementKeyword = "++";
        decrementKeyword = "--";
    }
    else if (generationMode == 2) {
        incrementKeyword = GetRandomSaneIncrementKeyword();
        decrementKeyword = GetRandomSaneDecrementKeyword();
    }
    else if (generationMode == 3) {
        incrementKeyword = GenerateOperatorGibberishName("+", 2, 20);
        decrementKeyword = GenerateOperatorGibberishName("-", 2, 20);
    } else {
        if (Random(1, 100) <= 50) {
            incrementKeyword = "++";
            decrementKeyword = "--";
        } else {
            if (Random(1, 100) <= 20) {
                incrementKeyword = GenerateOperatorGibberishName("+", 2, 20);
            } else {
                incrementKeyword = GetRandomSaneIncrementKeyword();
            }
            if (Random(1, 100) <= 20) {
                decrementKeyword = GenerateOperatorGibberishName("-", 2, 20);
            } else {
                decrementKeyword = GetRandomSaneDecrementKeyword();
            }
        }
    }
    HTVM_Append(returnArray, incrementKeyword);
    HTVM_Append(returnArray, decrementKeyword);
    return returnArray;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
// Start of Ternary Operator Keyword Generation
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
// Function to generate a random "sane" keyword for the first ternary operator (?)
function GetRandomSaneTernary1Keyword() {
    let saneNames = ["then", "ifTrue", "whenTrue", "isTrue", "trueCase", "consequent", "resultIfTrue", "outcome1", "positiveBranch", "yesPath", "affirmative", "doThis", "optionA", "firstChoice", "mainPath", "primaryResult", "directOutcome", "ifCondition", "queryThen", "checkThen", "evalTrue", "yieldTrue", "returnTrue", "getTrueVal", "trueValueIs", "TheResultIs", "PickThis", "ChooseA", "SelectIfTrue", "TrueBranchSelect", "ConditionalThen", "QueryResponse", "AskThenGive", "TruthValue", "LogicTrue", "BooleanYes", "ConfirmThen", "VerifyResult", "ValidateTrue", "IsTrueReturn", "IfYes", "ThenWhat", "Result1", "Path1", "Output1", "BranchA", "CaseTrue", "Scenario1", "PossibilityA", "Alternative1", "RouteOne", "FirstOption", "MainOutcome", "ConsequenceTrue", "PositiveResult", "TrueOutcome", "TruthPath", "AffirmativeOutcome", "DoThisPath", "ChooseThisOne", "SelectA", "TakeTrue", "TrueResultSelected", "YieldThis", "ReturnResultA", "GetValueA", "TrueExpression", "TheAnswerIs", "ThisWay", "PathYes", "BranchConfirm", "CheckMark", "ThumbsUpPath", "GoRoute", "ProceedPath", "FlowA", "StreamTrue", "ChannelYes", "PipeA", "OutputTrue", "SendTrue", "EmitYes", "ProduceA", "GenerateTrue", "CreateOptionA", "FormTrue", "ShapeResult1", "BuildBranchA", "ConstructCaseTrue", "FabricateScenario1", "AssemblePossibilityA", "ComposeAlternative1", "DesignRouteOne", "ArchitectFirstOption", "EngineerMainOutcome", "DevelopConsequenceTrue", "EvolvePositiveResult", "MatureTrueOutcome", "RipenTruthPath", "BlossomAffirmativeOutcome", "FlowerDoThisPath", "SproutChooseThisOne", "GerminateSelectA", "CultivateTakeTrue", "NurtureTrueResultSelected", "FosterYieldThis", "DevelopReturnResultA", "GrowGetValueA", "AdvanceTrueExpression", "ProgressTheAnswerIs", "StepThisWay", "NextPathYes", "ForwardBranchConfirm", "OnwardCheckMark", "HigherThumbsUpPath", "ElevateGoRoute", "LiftProceedPath", "RaiseFlowA", "AmplifyStreamTrue", "BoostChannelYes", "AugmentPipeA", "EnhanceOutputTrue", "OptimizeSendTrue", "RefineEmitYes", "SharpenProduceA", "HoneGenerateTrue", "TuneCreateOptionA", "CalibrateFormTrue", "AdjustShapeResult1", "PrecisionBuildBranchA", "AccuracyConstructCaseTrue", "ValidateFabricateScenario1", "VerifyAssemblePossibilityA", "ConfirmComposeAlternative1", "CheckDesignRouteOne", "TestArchitectFirstOption", "ProbeEngineerMainOutcome", "QueryDevelopConsequenceTrue", "AskEvolvePositiveResult", "InquireMatureTrueOutcome", "QuestionRipenTruthPath", "ExamineBlossomAffirmative", "InspectFlowerDoThisPath", "ScrutinizeSproutChooseOne", "AnalyzeGerminateSelectA", "DissectCultivateTakeTrue", "UnpackNurtureTrueResult", "DecodeFosterYieldThis", "DecipherDevelopReturnResultA", "InterpretGrowGetValueA", "UnderstandAdvanceTrueExpr", "GraspProgressTheAnswerIs", "ComprehendStepThisWay", "ApprehendNextPathYes", "PerceiveForwardBranchConf", "SenseOnwardCheckMark", "FeelHigherThumbsUpPath", "ImagineElevateGoRoute", "VisualizeLiftProceedPath", "PictureRaiseFlowA", "EnvisionAmplifyStreamTrue", "DreamBoostChannelYes", "FantasiizeAugmentPipeA", "SupposeEnhanceOutputTrue", "AssumeOptimizeSendTrue", "PresumeRefineEmitYes", "TheorizeSharpenProduceA", "HypothesizeHoneGenerateTrue", "PositTuneCreateOptionA", "PostulateCalibrateFormTrue", "ConjectureAdjustShapeResult1", "GuessPrecisionBuildBranchA", "SurmiseAccuracyConstructTrue", "InferValidateFabricateScen1", "DeduceVerifyAssemblePoss", "ReasonConfirmComposeAlt1", "LogicCheckDesignRouteOne", "CogitateTestArchitectFirst", "PonderProbeEngineerMain", "MuseQueryDevelopConsequence", "ReflectAskEvolvePositive", "MeditateInquireMatureTrue", "ContemplateQuestionRipen", "DeliberateExamineBlossom", "ConsiderInspectFlowerDo", "WeighScrutinizeSprout", "JudgeAnalyzeGerminate", "AssessDissectCultivate", "EvaluateUnpackNurture", "AppraiseDecodeFoster", "ReckonDecipherDevelop", "CalculateInterpretGrow", "ComputeUnderstandAdvance", "TallyGraspProgress", "SumComprehendStep", "TotalApprehendNext", "AggregatePerceiveForward", "SynthesizeSenseOnward", "CombineFeelHigher", "IntegrateImagineElevate", "UnifyVisualizeLift", "ConsolidatePictureRaise", "MergeEnvisionAmplify", "BlendDreamBoost", "FuseFantasiizeAugment", "JoinSupposeEnhance", "LinkAssumeOptimize", "ConnectPresumeRefine", "CoupleTheorizeSharpen", "PairHypothesizeHone", "MatchPositTune", "AlignPostulateCalibrate", "SynchronizeConjectureAdjust", "CoordinateGuessPrecision", "OrganizeSurmiseAccuracy", "StructureInferValidate", "SystematizeDeduceVerify", "ArrangeReasonConfirm", "OrderLogicCheck", "SequenceCogitateTest", "MarshalPonderProbe", "GroupMuseQuery", "CategorizeReflectAsk", "ClassifyMeditateInquire", "SortContemplateQuestion"];
    var randomIndex = Random(0, HTVM_Size(saneNames) - 1);
    return saneNames[randomIndex];
}
// Function to generate a random "sane" keyword for the second ternary operator (:)
function GetRandomSaneTernary2Keyword() {
    let saneNames = ["else", "ifFalse", "whenFalse", "isFalse", "falseCase", "alternative", "resultIfFalse", "outcome2", "negativeBranch", "noPath", "negative", "doThat", "optionB", "secondChoice", "alternatePath", "secondaryResult", "indirectOutcome", "elseCondition", "queryElse", "checkElse", "evalFalse", "yieldFalse", "returnFalse", "getFalseVal", "falseValueIs", "OtherwiseDo", "PickThat", "ChooseB", "SelectIfFalse", "FalseBranchSelect", "ConditionalElse", "ElseResponse", "AskThenDoOther", "FalsehoodValue", "LogicFalse", "BooleanNo", "DenyThen", "InvalidateResult", "ValidateFalse", "IsFalseReturn", "IfNo", "ElseWhat", "Result2", "Path2", "Output2", "BranchB", "CaseFalse", "Scenario2", "PossibilityB", "Alternative2", "RouteTwo", "SecondOption", "AlternateOutcome", "ConsequenceFalse", "NegativeResult", "FalseOutcome", "FalsehoodPath", "NegativeOutcome", "DoThatPath", "ChooseThatOne", "SelectB", "TakeFalse", "FalseResultSelected", "YieldThat", "ReturnResultB", "GetValueB", "FalseExpression", "TheOtherAnswer", "ThatWay", "PathNo", "BranchDeny", "CrossMark", "ThumbsDownPath", "StopRoute", "RecedePath", "FlowB", "StreamFalse", "ChannelNo", "PipeB", "OutputFalse", "SendFalse", "EmitNo", "ProduceB", "GenerateFalse", "CreateOptionB", "FormFalse", "ShapeResult2", "BuildBranchB", "ConstructCaseFalse", "FabricateScenario2", "AssemblePossibilityB", "ComposeAlternative2", "DesignRouteTwo", "ArchitectSecondOption", "EngineerAlternateOutcome", "DevelopConsequenceFalse", "EvolveNegativeResult", "MatureFalseOutcome", "RipenFalsehoodPath", "BlossomNegativeOutcome", "FlowerDoThatPath", "SproutChooseThatOne", "GerminateSelectB", "CultivateTakeFalse", "NurtureFalseResultSelect", "FosterYieldThat", "DevelopReturnResultB", "GrowGetValueB", "AdvanceFalseExpression", "ProgressTheOtherAnswer", "StepThatWay", "NextPathNo", "ForwardBranchDeny", "OnwardCrossMark", "HigherThumbsDownPath", "ElevateStopRoute", "LiftRecedePath", "RaiseFlowB", "AmplifyStreamFalse", "BoostChannelNo", "AugmentPipeB", "EnhanceOutputFalse", "OptimizeSendFalse", "RefineEmitNo", "SharpenProduceB", "HoneGenerateFalse", "TuneCreateOptionB", "CalibrateFormFalse", "AdjustShapeResult2", "PrecisionBuildBranchB", "AccuracyConstructCaseFalse", "ValidateFabricateScenario2", "VerifyAssemblePossibilityB", "ConfirmComposeAlternative2", "CheckDesignRouteTwo", "TestArchitectSecondOption", "ProbeEngineerAlternateOutcome", "QueryDevelopConsequenceFalse", "AskEvolveNegativeResult", "InquireMatureFalseOutcome", "QuestionRipenFalsehoodPath", "ExamineBlossomNegative", "InspectFlowerDoThatPath", "ScrutinizeSproutChooseThat", "AnalyzeGerminateSelectB", "DissectCultivateTakeFalse", "UnpackNurtureFalseResult", "DecodeFosterYieldThat", "DecipherDevelopReturnResB", "InterpretGrowGetValueB", "UnderstandAdvanceFalseExpr", "GraspProgressTheOtherAnswer", "ComprehendStepThatWay", "ApprehendNextPathNo", "PerceiveForwardBranchDeny", "SenseOnwardCrossMark", "FeelHigherThumbsDownPath", "ImagineElevateStopRoute", "VisualizeLiftRecedePath", "PictureRaiseFlowB", "EnvisionAmplifyStreamFalse", "DreamBoostChannelNo", "FantasiizeAugmentPipeB", "SupposeEnhanceOutputFalse", "AssumeOptimizeSendFalse", "PresumeRefineEmitNo", "TheorizeSharpenProduceB", "HypothesizeHoneGenerateFalse", "PositTuneCreateOptionB", "PostulateCalibrateFormFalse", "ConjectureAdjustShapeResult2", "GuessPrecisionBuildBranchB", "SurmiseAccuracyConstructFalse", "InferValidateFabricateScen2", "DeduceVerifyAssemblePossB", "ReasonConfirmComposeAlt2", "LogicCheckDesignRouteTwo", "CogitateTestArchitectSecond", "PonderProbeEngineerAlternate", "MuseQueryDevelopConsequenceF", "ReflectAskEvolveNegative", "MeditateInquireMatureFalse", "ContemplateQuestionRipenF", "DeliberateExamineBlossomNeg", "ConsiderInspectFlowerDoThat", "WeighScrutinizeSproutChoose", "JudgeAnalyzeGerminateSelectB", "AssessDissectCultivateTakeF", "EvaluateUnpackNurtureFalse", "AppraiseDecodeFosterYield", "ReckonDecipherDevelopReturn", "CalculateInterpretGrowValueB", "ComputeUnderstandAdvanceFalse", "TallyGraspProgressOther", "SumComprehendStepThatWay", "TotalApprehendNextPathNo", "AggregatePerceiveForwardDeny", "SynthesizeSenseOnwardCross", "CombineFeelHigherThumbsDown", "IntegrateImagineElevateStop", "UnifyVisualizeLiftRecede", "ConsolidatePictureRaiseFlowB", "MergeEnvisionAmplifyStreamF", "BlendDreamBoostChannelNo", "FuseFantasiizeAugmentPipeB", "JoinSupposeEnhanceOutputF", "LinkAssumeOptimizeSendF", "ConnectPresumeRefineEmitNo", "CoupleTheorizeSharpenProdB", "PairHypothesizeHoneGenerateF", "MatchPositTuneCreateOptionB", "AlignPostulateCalibrateFormF", "SynchronizeConjectureAdjustF", "CoordinateGuessPrecisionBuildB", "OrganizeSurmiseAccuracyConstF", "StructureInferValidateFabric2", "SystematizeDeduceVerifyAssB", "ArrangeReasonConfirmComposeA2", "OrderLogicCheckDesignRouteTwo", "SequenceCogitateTestArchSec", "MarshalPonderProbeEngineerAlt", "GroupMuseQueryDevelopConseqF", "CategorizeReflectAskEvolveN", "ClassifyMeditateInquireMatF", "SortContemplateQuestionRipenF"];
    var randomIndex = Random(0, HTVM_Size(saneNames) - 1);
    return saneNames[randomIndex];
}
// UPDATED function to generate Ternary Operator keyword variants with mode control
function GenerateTernaryOperators(generationMode = 0) {
    var ternary1Keyword;
    var ternary2Keyword;
    let returnArray = [];
    if (generationMode == 1) {
        ternary1Keyword = "?";
        ternary2Keyword = ":";
    }
    else if (generationMode == 2) {
        ternary1Keyword = GetRandomSaneTernary1Keyword();
        ternary2Keyword = GetRandomSaneTernary2Keyword();
    }
    else if (generationMode == 3) {
        ternary1Keyword = GenerateGibberishName(2, 20);
        ternary2Keyword = GenerateGibberishName(2, 20);
    } else {
        if (Random(1, 100) <= 50) {
            ternary1Keyword = "?";
            ternary2Keyword = ":";
        } else {
            if (Random(1, 100) <= 20) {
                ternary1Keyword = GenerateGibberishName(2, 20);
            } else {
                ternary1Keyword = GetRandomSaneTernary1Keyword();
            }
            if (Random(1, 100) <= 20) {
                ternary2Keyword = GenerateGibberishName(2, 20);
            } else {
                ternary2Keyword = GetRandomSaneTernary2Keyword();
            }
        }
    }
    HTVM_Append(returnArray, ternary1Keyword);
    HTVM_Append(returnArray, ternary2Keyword);
    return returnArray;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
// Start of Assignment Operator Keyword Generation
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
// --- Helper functions for "sane" assignment operator keywords ---
function GetRandomSane_Assign_Keyword() {
    let saneNames = ["assign", "set", "is", "becomes", "equals", "letBe", "store", "defineAs", "setTo", "make", "transfer", "copyTo", "initAs", "valueIs", "varIs", "dataIs", "bindTo", "linkTo", "holdVal", "giveVal", "acceptVal", "fixVal", "placeVal", "gets", "receives", "takes"];
    return saneNames[Random(0, HTVM_Size(saneNames) - 1)];
}
function GetRandomSane_AssignAdd_Keyword() {
    let saneNames = ["addAssign", "plusEquals", "incrementBy", "addTo", "sumAssign", "increaseBy", "accumulate", "appendNum", "augAssign", "combineAdd", "mergeSum", "growBy", "extendSum", "amassAdd", "PlusEq", "sumTo", "tallyUp"];
    return saneNames[Random(0, HTVM_Size(saneNames) - 1)];
}
function GetRandomSane_AssignConcat_Keyword() {
    let saneNames = ["concatAssign", "appendStr", "stringAdd", "dotEquals", "joinAssign", "textAppend", "mergeStr", "combineText", "chainStr", "linkText", "uniteStr", "fuseText", "weldStr", "CatEq", "stringJoin", "attachText"];
    return saneNames[Random(0, HTVM_Size(saneNames) - 1)];
}
function GetRandomSane_AssignSub_Keyword() {
    let saneNames = ["subAssign", "minusEquals", "decrementBy", "subFrom", "deductAssign", "decreaseBy", "reduceBy", "diminishBy", "shrinkBy", "lessenBy", "withdrawFrom", "MinusEq", "takeAway", "deductFrom"];
    return saneNames[Random(0, HTVM_Size(saneNames) - 1)];
}
function GetRandomSane_AssignMul_Keyword() {
    let saneNames = ["mulAssign", "timesEquals", "multiplyBy", "scaleBy", "productAssign", "factorAssign", "amplifyBy", "magnifyBy", "replicateBy", "TimesEq", "MultEq", "productIs"];
    return saneNames[Random(0, HTVM_Size(saneNames) - 1)];
}
function GetRandomSane_AssignDiv_Keyword() {
    let saneNames = ["divAssign", "divideEquals", "divideBy", "ratioAssign", "quotientAssign", "shareBy", "splitBy", "partitionBy", "DivEq", "SlashEq", "quotientIs"];
    return saneNames[Random(0, HTVM_Size(saneNames) - 1)];
}
function GetRandomSane_AssignMod_Keyword() {
    let saneNames = ["modAssign", "moduloEquals", "remainderAssign", "modBy", "cycleAssign", "wrapAssign", "ModEq", "RemEq", "PercentEq", "moduloIs"];
    return saneNames[Random(0, HTVM_Size(saneNames) - 1)];
}
function GetRandomSane_AssignShiftLeft_Keyword() {
    let saneNames = ["shiftLAssign", "lshEquals", "bitShiftLStore", "moveBitsLSet", "slideLStore", "LShiftEq", "LeftShiftAssign", "LSLset", "bitSlideL"];
    return saneNames[Random(0, HTVM_Size(saneNames) - 1)];
}
function GetRandomSane_AssignShiftRight_Keyword() {
    let saneNames = ["shiftRAssign", "rshEquals", "bitShiftRStore", "moveBitsRSet", "slideRStore", "RShiftEq", "RightShiftAssign", "RSRset", "bitSlideR"];
    return saneNames[Random(0, HTVM_Size(saneNames) - 1)];
}
function GetRandomSane_AssignUShiftRight_Keyword() {
    let saneNames = ["uShiftRAssign", "urshEquals", "logicShiftRStore", "zeroFillRSet", "positiveRStore", "URShiftEq", "UShiftAssign", "USRset", "logicSlideR"];
    return saneNames[Random(0, HTVM_Size(saneNames) - 1)];
}
function GetRandomSane_AssignBitAnd_Keyword() {
    let saneNames = ["bitAndAssign", "andEquals", "maskAssign", "intersectStore", "filterAndSet", "BitAndEq", "AmpersandEq", "bitwiseAndSet"];
    return saneNames[Random(0, HTVM_Size(saneNames) - 1)];
}
function GetRandomSane_AssignBitOr_Keyword() {
    let saneNames = ["bitOrAssign", "orEquals", "setBitsStore", "unionOrSet", "includeOrStore", "BitOrEq", "PipeEq", "bitwiseOrSet"];
    return saneNames[Random(0, HTVM_Size(saneNames) - 1)];
}
function GetRandomSane_AssignBitXor_Keyword() {
    let saneNames = ["bitXorAssign", "xorEquals", "toggleBitsStore", "exclusiveOrSet", "flipBitsStore", "BitXorEq", "CaretEq", "bitwiseXorSet"];
    return saneNames[Random(0, HTVM_Size(saneNames) - 1)];
}
// Main function to generate all 13 assignment operator keywords based on mode
function GenerateAllAssignmentOperators(generationMode = 0) {
    let operatorKeywords = [];
    var currentKeyword;
    if (generationMode == 1) { currentKeyword := "=" }
    else if (generationMode == 2) { currentKeyword := GetRandomSane_Assign_Keyword() }
    else if (generationMode == 3) { currentKeyword := GenerateGibberishName(2, 10) }
    else {
        var r = Random(1, 100);
        if (r <= 50) { currentKeyword := "=" }
        else if (r <= 80) { currentKeyword := GetRandomSane_Assign_Keyword() }
    }
    HTVM_Append(operatorKeywords, currentKeyword);
    if (generationMode == 1) { currentKeyword := "+=" }
    else if (generationMode == 2) { currentKeyword := GetRandomSane_AssignAdd_Keyword() }
    else if (generationMode == 3) { currentKeyword := GenerateGibberishName(2, 10) }
    else {
        var r = Random(1, 100);
        if (r <= 50) { currentKeyword := "+=" }
        else if (r <= 80) { currentKeyword := GetRandomSane_AssignAdd_Keyword() }
    }
    HTVM_Append(operatorKeywords, currentKeyword);
    if (generationMode == 1) { currentKeyword := ".=" }
    else if (generationMode == 2) { currentKeyword := GetRandomSane_AssignConcat_Keyword() }
    else if (generationMode == 3) { currentKeyword := GenerateGibberishName(2, 10) }
    else {
        var r = Random(1, 100);
        if (r <= 50) { currentKeyword := ".=" }
        else if (r <= 80) { currentKeyword := GetRandomSane_AssignConcat_Keyword() }
    }
    HTVM_Append(operatorKeywords, currentKeyword);
    if (generationMode == 1) { currentKeyword := "-=" }
    else if (generationMode == 2) { currentKeyword := GetRandomSane_AssignSub_Keyword() }
    else if (generationMode == 3) { currentKeyword := GenerateGibberishName(2, 10) }
    else {
        var r = Random(1, 100);
        if (r <= 50) { currentKeyword := "-=" }
        else if (r <= 80) { currentKeyword := GetRandomSane_AssignSub_Keyword() }
    }
    HTVM_Append(operatorKeywords, currentKeyword);
    if (generationMode == 1) { currentKeyword := "*=" }
    else if (generationMode == 2) { currentKeyword := GetRandomSane_AssignMul_Keyword() }
    else if (generationMode == 3) { currentKeyword := GenerateGibberishName(2, 10) }
    else {
        var r = Random(1, 100);
        if (r <= 50) { currentKeyword := "*=" }
        else if (r <= 80) { currentKeyword := GetRandomSane_AssignMul_Keyword() }
    }
    HTVM_Append(operatorKeywords, currentKeyword);
    if (generationMode == 1) { currentKeyword := "/=" }
    else if (generationMode == 2) { currentKeyword := GetRandomSane_AssignDiv_Keyword() }
    else if (generationMode == 3) { currentKeyword := GenerateGibberishName(2, 10) }
    else {
        var r = Random(1, 100);
        if (r <= 50) { currentKeyword := "/=" }
        else if (r <= 80) { currentKeyword := GetRandomSane_AssignDiv_Keyword() }
    }
    HTVM_Append(operatorKeywords, currentKeyword);
    if (generationMode == 1) { currentKeyword := "%=" }
    else if (generationMode == 2) { currentKeyword := GetRandomSane_AssignMod_Keyword() }
    else if (generationMode == 3) { currentKeyword := GenerateGibberishName(2, 10) }
    else {
        var r = Random(1, 100);
        if (r <= 50) { currentKeyword := "%=" }
        else if (r <= 80) { currentKeyword := GetRandomSane_AssignMod_Keyword() }
    }
    HTVM_Append(operatorKeywords, currentKeyword);
    if (generationMode == 1) { currentKeyword := "<<=" }
    else if (generationMode == 2) { currentKeyword := GetRandomSane_AssignShiftLeft_Keyword() }
    else if (generationMode == 3) { currentKeyword := GenerateGibberishName(3, 10) }
    else {
        var r = Random(1, 100);
        if (r <= 50) { currentKeyword := "<<=" }
        else if (r <= 80) { currentKeyword := GetRandomSane_AssignShiftLeft_Keyword() }
    }
    HTVM_Append(operatorKeywords, currentKeyword);
    if (generationMode == 1) { currentKeyword := ">>=" }
    else if (generationMode == 2) { currentKeyword := GetRandomSane_AssignShiftRight_Keyword() }
    else if (generationMode == 3) { currentKeyword := GenerateGibberishName(3, 10) }
    else {
        var r = Random(1, 100);
        if (r <= 50) { currentKeyword := ">>=" }
        else if (r <= 80) { currentKeyword := GetRandomSane_AssignShiftRight_Keyword() }
    }
    HTVM_Append(operatorKeywords, currentKeyword);
    if (generationMode == 1) { currentKeyword := ">>>=" }
    else if (generationMode == 2) { currentKeyword := GetRandomSane_AssignUShiftRight_Keyword() }
    else if (generationMode == 3) { currentKeyword := GenerateGibberishName(4, 10) }
    else {
        var r = Random(1, 100);
        if (r <= 50) { currentKeyword := ">>>=" }
        else if (r <= 80) { currentKeyword := GetRandomSane_AssignUShiftRight_Keyword() }
    }
    HTVM_Append(operatorKeywords, currentKeyword);
    if (generationMode == 1) { currentKeyword := "&=" }
    else if (generationMode == 2) { currentKeyword := GetRandomSane_AssignBitAnd_Keyword() }
    else if (generationMode == 3) { currentKeyword := GenerateGibberishName(2, 10) }
    else {
        var r = Random(1, 100);
        if (r <= 50) { currentKeyword := "&=" }
        else if (r <= 80) { currentKeyword := GetRandomSane_AssignBitAnd_Keyword() }
    }
    HTVM_Append(operatorKeywords, currentKeyword);
    if (generationMode == 1) { currentKeyword := "|=" }
    else if (generationMode == 2) { currentKeyword := GetRandomSane_AssignBitOr_Keyword() }
    else if (generationMode == 3) { currentKeyword := GenerateGibberishName(2, 10) }
    else {
        var r = Random(1, 100);
        if (r <= 50) { currentKeyword := "|=" }
        else if (r <= 80) { currentKeyword := GetRandomSane_AssignBitOr_Keyword() }
    }
    HTVM_Append(operatorKeywords, currentKeyword);
    if (generationMode == 1) { currentKeyword := "^=" }
    else if (generationMode == 2) { currentKeyword := GetRandomSane_AssignBitXor_Keyword() }
    else if (generationMode == 3) { currentKeyword := GenerateGibberishName(2, 10) }
    else {
        var r = Random(1, 100);
        if (r <= 50) { currentKeyword := "^=" }
        else if (r <= 80) { currentKeyword := GetRandomSane_AssignBitXor_Keyword() }
    }
    HTVM_Append(operatorKeywords, currentKeyword);
    return operatorKeywords;
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
for (let A_Index5 = 0; A_Index5 < HTVM_Size(assignmentOpsGenerated) + 0; A_Index5++) {
    print("  " + defaultOperatorSymbols[A_Index5] + " -> '" + assignmentOpsGenerated[A_Index5] + "'");
}
assignmentOpsGenerated = GenerateAllAssignmentOperators();
for (let A_Index6 = 0; A_Index6 < HTVM_Size(assignmentOpsGenerated) + 0; A_Index6++) {
    print("  " + defaultOperatorSymbols[A_Index6] + " -> '" + assignmentOpsGenerated[A_Index6] + "' (2nd random call)");
}
print("Mode 1 (Defaults):");
assignmentOpsGenerated = GenerateAllAssignmentOperators(1);
for (let A_Index7 = 0; A_Index7 < HTVM_Size(assignmentOpsGenerated) + 0; A_Index7++) {
    print("  " + defaultOperatorSymbols[A_Index7] + " -> '" + assignmentOpsGenerated[A_Index7] + "'");
}
print("Mode 2 (Random Sane):");
assignmentOpsGenerated = GenerateAllAssignmentOperators(2);
for (let A_Index8 = 0; A_Index8 < HTVM_Size(assignmentOpsGenerated) + 0; A_Index8++) {
    print("  " + defaultOperatorSymbols[A_Index8] + " -> '" + assignmentOpsGenerated[A_Index8] + "'");
}
print("Mode 3 (Gibberish):");
assignmentOpsGenerated = GenerateAllAssignmentOperators(3);
for (let A_Index9 = 0; A_Index9 < HTVM_Size(assignmentOpsGenerated) + 0; A_Index9++) {
    print("  " + defaultOperatorSymbols[A_Index9] + " -> '" + assignmentOpsGenerated[A_Index9] + "'");
}
print("-------------------------------------");
let outArrFromStates = [];
outArrFromStates = GenerateRandomizedStates();
print("--- Output from GenerateRandomizedStates (Unchanged Function) ---");
for (let A_Index10 = 0; A_Index10 < HTVM_Size(outArrFromStates) + 0; A_Index10++) {
    print("State " + STR(A_Index10) + ": " + outArrFromStates[A_Index10]);
}
print(";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;");