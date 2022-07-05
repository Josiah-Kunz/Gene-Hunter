#include "TypeUnitTestUtilities.h"


bool UTypeUnitTestUtilities::TestCombatAnalysis(const TArray<UType*>& AllTypes, const TArray<UType*>& TypesToAnalyze,
	const int NumOpponentTypes, const FFloatRange Range, const bool bAtk, const EAttackModifierMode Mode,
	const TArray<FTypeArray1D*>& Expected, FString& Description, const bool bDebug)
{
	// Get array of FTypeArray1D (either defenders or attackers)
	const TArray<FTypeArray1D*> OpponentTypes = GetAllTypeCombinations(AllTypes, NumOpponentTypes);
	
	// Get the UTypes (actual) that fall within the given range
	const TArray<FTypeArray1D*> Analysis = Analyze(TypesToAnalyze, OpponentTypes,
				Range,
				Mode,
				bAtk,
				bDebug
			);

	// Test it
	return FTypeArray1D::ArrayOfTypeArray1DsAreEqual(Analysis, Expected, Description);
}

bool UTypeUnitTestUtilities::TestAnalyzeAll(TArray<UType*>& AllTypes, const int NumTestedTypes, const int NumUntestedTypes,
		const FFloatRange Range, const bool bAnalyzeAtk, const EAttackModifierMode Mode,
		const TArray<FTypeArray2D*>& Expected, FString& Description)
{
	
	// Get the FTypeArray2D (actual) that fall within the given range
	TArray<FTypeArray2D> Analysis;
	AnalyzeAll(AllTypes, NumTestedTypes, NumUntestedTypes, Range, bAnalyzeAtk, Mode, Analysis);
	TArray<FTypeArray2D*> AnalysisPointer;
	for(FTypeArray2D& TypeArray2D : Analysis)
		AnalysisPointer.Add(std::addressof(TypeArray2D));

	// Test it
	return FTypeArray2D::ArrayOfTypeArray2DsAreEqual(AnalysisPointer, Expected, Description);
}

void UTypeUnitTestUtilities::PrintStatistics(const int NumAttackers, const int NumDefenders, const FFloatRange Range,
	const EAttackModifierMode Mode, const bool bAtk, const bool bPrintToConsole, const bool bPrintToFile,
	const bool bPrintToFileLaTeX, TArray<UType*>& Exclude, const FString PrintDirectory)
{

	// Get all types except exclusions
	TArray<UType*> AllTypes;
	UType::GetAllTypes(AllTypes, Exclude);

	// Perform analysis
	TArray<FTypeArray2D> Analysis;
	AnalyzeAll(
		AllTypes,
		bAtk ? NumAttackers : NumDefenders,
		bAtk ? NumDefenders : NumAttackers,
		Range, bAtk, Mode, Analysis);

	// Sort analysis
	Analysis.Sort([](const FTypeArray2D& A, const FTypeArray2D& B)
	{
		return A.Array2.Num() > B.Array2.Num();
	});

	// LaTeX text header
	FString NumAtkText = FString::FromInt(NumAttackers);
	FString NumDefText = FString::FromInt(NumDefenders);
	FString AttackingText = bAtk ? "Attacking" : "Defending";
	const FString EffectiveText = Range.HasLowerBound() ?
		(bAtk ? "Effective" : "Weak") :
		(bAtk ? "Ineffective" : "Resisted");
	FString LaTeXText = "";
	LaTeXText += "\\twocolumn\n";
	LaTeXText += "\\begin{longtblr}[\n";
	LaTeXText += FString::Printf(TEXT("\tcaption = {%sv%s %s %s},\n"),
		*NumAtkText,
		*NumDefText,
		*AttackingText,
		*EffectiveText);
	LaTeXText += FString::Printf(TEXT("\tlabel = {%sv%s-%s-%s},\n"),
		*NumAtkText,
		*NumDefText,
		*AttackingText,
		*EffectiveText);
	LaTeXText += "]{\n";
	LaTeXText += "\tcolspec = {XXX}, width = 0.95\\linewidth,\n";
	LaTeXText += "\thline{1,Z} = {2pt},\n";
	LaTeXText += "\thlines,\n";
	LaTeXText += "\trow{1-3,X,Y,Z} = {font=\\bfseries},\n";
	LaTeXText += "}\n";

	// Print header in console
	FString ConsoleText = "";
	ConsoleText += UGeneHunterBPLibrary::LINE_SEPARATOR;
	ConsoleText += "\n";
	ConsoleText += "Analysis when ";
	AttackingText = bAtk ? "attacking" : "defending";
	ConsoleText += AttackingText;
	ConsoleText += "\n";

	// Number of attackers/defenders
	NumAtkText = (NumAttackers == 1 ? "Single" : (NumAttackers == 2 ? "Dual" : FString::FromInt(NumAttackers)));
	NumDefText = (NumDefenders == 1 ? "single" : (NumDefenders == 2 ? "dual" : FString::FromInt(NumDefenders)));
	ConsoleText += "\t";
	ConsoleText += NumAtkText + "-Type Attacker\n";
	ConsoleText += "\tvs " + NumDefText + "-Type Defender\n";

	// Mode
	FString ModeText;
	ConsoleText += "\tAttack mode: ";
	switch(Mode)
	{
	case EAttackModifierMode::Coverage:
		ModeText = "Coverage";
		break;
	case EAttackModifierMode::MultiType:
		ModeText = "Multi-Type";
		break;
	default:
		ConsoleText+= "ERROR! Mode not defined in code. Please fix UType::PrintStatistics in Type.cpp.";
		UE_LOG(LogTemp, Error, TEXT("%s:"), *ConsoleText);
		return;
	}
	ConsoleText += ModeText;
	ConsoleText += "\n";
	
	
	// Range
	FString RangeText;
	UGeneHunterBPLibrary::RangeToString(Range, RangeText);
	ConsoleText += FString::Printf(TEXT("\t%s\n"), *RangeText);
	
	// Last line for header
	ConsoleText += UGeneHunterBPLibrary::LINE_SEPARATOR;
	ConsoleText += "\n\n";
	
	// Print results
	for(FTypeArray2D TypeArray2D : Analysis)
	{
		ConsoleText += FString::Printf(TEXT("(%s) %s:\n"),
		*FString::FromInt(TypeArray2D.Array2.Num()),
		*UType::ArrayToFString(TypeArray2D.Array));

		LaTeXText += FString::Printf(TEXT("\t:%s:&{(%s)\\\\\n"),
		*UType::ArrayToFString(TypeArray2D.Array),
		*FString::FromInt(TypeArray2D.Array2.Num())
		);

		// Check none
		if (TypeArray2D.Array2.Num() == 0)
		{
			ConsoleText += "\tNONE!\n";
			LaTeXText += "\tNONE\\\\}\n";
			continue;
		}

		// Get names
		FString DefenderNames = "";
		int i=0;
		int LineCount = 0;
		for(const UType* Defender : TypeArray2D.Array2)
		{

			// Check line count
			LineCount++;
			if (LineCount > MAX_LATEX_LINES)
			{
				LaTeXText += "\t...\\\\\n";
				break;
			}

			// Add defender names
			DefenderNames += Defender->GetName() + " ";
			i++;
			if (i>=NumDefenders)
			{
				ConsoleText += FString::Printf(TEXT("\t%s\n"), *DefenderNames);
				LaTeXText += FString::Printf(TEXT("\t%s\\\\\n"),
					*DefenderNames
					);
				DefenderNames = "";
				i=0;
			}
		}

		// Blank line
		ConsoleText += "\n";
		LaTeXText += "\t}\\\\\n\n";
	}

	// End
	ConsoleText += UGeneHunterBPLibrary::LINE_SEPARATOR;
	LaTeXText += "\\end{longtblr}\n";
	LaTeXText += "\\onecolumn\n";

	// Print
	if (bPrintToConsole)
		UE_LOG(LogTemp, Display, TEXT("\n\n%s"), *ConsoleText);
	if (bPrintToFile)
	{
		const FString Extension = bPrintToFileLaTeX ? "tex" : "txt";
		FString FileName = FString::Printf(TEXT("%s%sanalysis_%sv%s_%s_%s_%s.%s"),
					*FPaths::ProjectDir(),
					*PrintDirectory,
					*NumAtkText, *NumDefText,
					*AttackingText,
					*ModeText,
					*RangeText,
					*Extension);
		FileName = FPaths::ConvertRelativePathToFull(FileName);
		const bool bSaved = FFileHelper::SaveStringToFile(
			bPrintToFileLaTeX ? LaTeXText : ConsoleText,
			*FileName,
			FFileHelper::EEncodingOptions::AutoDetect,
			&IFileManager::Get(),
			FILEWRITE_EvenIfReadOnly
			);

		if (bSaved)
		{
			UE_LOG(LogTemp, Display, TEXT("\n%s\nSaved @ %s\n%s"),
				*UGeneHunterBPLibrary::LINE_SEPARATOR,
				*FileName,
				*UGeneHunterBPLibrary::LINE_SEPARATOR);
		}else
			UE_LOG(LogTemp, Warning, TEXT("\n%s\nFailed to save @ %s\n%s"),
				*UGeneHunterBPLibrary::LINE_SEPARATOR,
				*FileName,
				*UGeneHunterBPLibrary::LINE_SEPARATOR);
	}
	
}


TArray<FTypeArray1D*> UTypeUnitTestUtilities::GetAllTypeCombinations(const TArray<UType*>& Types, const int NumTypes)
{

	TArray<FTypeArray1D*> Ret = {};
	
	// User is being dumb
	if (Types.Num() == 0 || NumTypes < 1 || Types.Num() < NumTypes)
		return Ret;

	// Setup trackers
	TArray Indices = {0};
	for(int i=1; i<NumTypes; i++)
		Indices.Add(Indices[i-1] + 1);

	// Loop until options are exhausted
	int Failsafe = 0;
	while (Failsafe < UGeneHunterBPLibrary::MAX_ITERATIONS && Indices[0] <= Types.Num() - NumTypes)
	{

		// Populate TypeInfo
		FTypeArray1D* TypeInfo = new FTypeArray1D{{}};
		for (int i=0; i<NumTypes;i++)
			TypeInfo->Array.Add(Types[Indices[i]]);

		// Add newest entry
		Ret.Add(TypeInfo);
		
		// Iterate
		if (IncrementIndices(Types, Indices)) // Never able to iterate; must be at the end of all possible Type combinations
			break;
		Failsafe++;
	}

	// Return
	return Ret;
	
}


TArray<FTypeArray1D*> UTypeUnitTestUtilities::Analyze(const TArray<UType*>& TypesToAnalyze, const TArray<FTypeArray1D*>& AgainstTypes,
	const FFloatRange Range, const EAttackModifierMode Mode, const bool bAtk, const bool bDebug)
{
	
	TArray<FTypeArray1D*> Ret;
	float OverallModifier = 1;

	// Loop over, e.g., {{Fire, Water}, {Fire, Grass}, {Grass, Water}, ...}
	for(FTypeArray1D* AgainstInfo : AgainstTypes)
	{

		// Debug
		if (bDebug)
			UE_LOG(LogTemp, Display, TEXT("======================="));

		// Rely on another function
		const float Modifier = UType::GetNetModifier(bAtk ? TypesToAnalyze : AgainstInfo->Array,
			bAtk ? AgainstInfo->Array : TypesToAnalyze,
			Mode, bDebug);

		// All done with combining types; add?
		if (Range.Contains(Modifier))
			Ret.Add(AgainstInfo);
		
		
		// Initialize Modifier
		UType::InitializeModifier(OverallModifier, Mode);
	}

	// Return result
	return Ret;
}

bool UTypeUnitTestUtilities::IncrementIndices(const TArray<UType*>& Types, TArray<int>& Indices)
{

	/*
	 *	In this example, we have five types and three indices:
	 *		Indices = {1, 2, 5}
	 *		Types.Num() ==> 5
	 */
	
	bool Ret = true;
	int i=Indices.Num()-1;	// Start at the last index (e.g., the "5" in {1, 2, 5})
	while (Ret && i>=0)
	{
		Indices[i]++;		// Increment this index (e.g., the "5" becomes a "6", which is over cap)
		if (Indices[i] >= Types.Num() - ((Indices.Num()-1)-i))	// i=2's cap is 5; i=1's cap is 4; etc.
			{
			i--;			// Go to the previous index (e.g, the "2")
			} else
			{
				Ret = false;
				for(int j=i+1; j<Indices.Num();j++)	// This i works! Reset its following Indices (e.g., if i=1 was validly set to "3", set i=2 to "4")
					Indices[j] = Indices[i]+(j-i);
			}
	}
	return Ret;
}

void UTypeUnitTestUtilities::AnalyzeAll(TArray<UType*>& Types, const int NumTestedTypes, const int NumUntestedTypes,
	const FFloatRange Range, const bool bAnalyzeAtk, const EAttackModifierMode Mode, TArray<FTypeArray2D>& Result)
{


	/*
	 *	Visualization of algorithm
	 *	==========================
	 *
	 *		- In this example, there are 10 Types A-J
	 *		- In this example, NumTestedTypes=4, NumUntestedTypes=1, Range=[1, open), bAnalyzeAtk=true
	 *		- The iteration count is boxed on the left
	 *		- E.g., in the zeroth iteration, Types ABCD are tested against the "first row" (defender; presumably type A)
	 *
	 *	0 |
	 *	--
	 *		A B C D E F G H I J
	 *		0 1 2 3
	 *
	 *	1 |
	 *	--
	 *		A B C D E F G H I J
	 *		0 1 2   3
	 *
	 *	...
	 *
	 *	6 |
	 *	--
	 *		A B C D E F G H I J
	 *		0 1 2             3
	 *
	 *	7 |
	 *	--
	 *		A B C D E F G H I J
	 *		0 1   2 3
	 *
	 *	Penultimate |
	 *	------------
	 *		A B C D E F G H I J
	 *		          0   1 2 3
	 *
	 *	Final |
	 *	------
	 *		A B C D E F G H I J
	 *		            0 1 2 3
	 *
	 */

	// User is being dumb
	if (Types.Num() == 0 ||
		NumTestedTypes < 1 || Types.Num() < NumTestedTypes ||
		NumUntestedTypes < 1 || Types.Num() < NumUntestedTypes)
		return;

	// Vars
	TArray TestedIndices = {0};				// The indices of the Types in TestedTypes. E.g., if Fire/Water is being tested, this may be {4, 13} (or whatever).
	TArray UntestedIndices = {0};			// Same with what's being tested against
	TArray<UType*> TypeCandidates;			// If bAtk, the combination that is defending
	int i;									// Dummy int
	TArray<UType*> AtkTypes, DefTypes;
	float Modifier;							// The result of the (incremental) test
	
	// Initialize Types being tested
	for(i=1; i<NumTestedTypes; i++)
		TestedIndices.Add(TestedIndices[i-1] + 1);	// {0, 1, 2, 3}
	
	// Loop until all options are exhausted
	int Failsafe1 = 0, Failsafe2;
	while (Failsafe1 < UGeneHunterBPLibrary::MAX_ITERATIONS && TestedIndices[0] <= Types.Num() - NumTestedTypes)
	{

		// Get the attacking Type combination based on current indices
		FTypeArray2D A;
		Result.Add(A);
		for (i=0; i<NumTestedTypes;i++)
			Result.Last().Array.Add(Types[TestedIndices[i]]);
		
		// Reset defending indices (since we're about to iterate over them)
		UntestedIndices = {0};
		for(i=1; i<NumUntestedTypes;i++)
			UntestedIndices.Add(UntestedIndices[i-1]+1);
		
		// Test this combination's effectiveness against all other Types
		Failsafe2 = 0;
		while (Failsafe2 < UGeneHunterBPLibrary::MAX_ITERATIONS && UntestedIndices[0] <= Types.Num() - NumUntestedTypes)
		{

			// Get the attacking Type combination based on indices
			TypeCandidates.Empty();
			for (i=0; i<NumUntestedTypes;i++)
				TypeCandidates.Add(Types[UntestedIndices[i]]);

			// Get the [best] modifier (this is the meat; everything else is just bookkeeping!)
			AtkTypes = bAnalyzeAtk ? Result.Last().Array : TypeCandidates;
			DefTypes = bAnalyzeAtk ? TypeCandidates : Result.Last().Array;
			Modifier = UType::GetNetModifier(AtkTypes, DefTypes, Mode);
			
			// Check success
			if (Range.Contains(Modifier))
				for (UType* SuccessfulType : TypeCandidates)
					Result.Last().Array2.Add(SuccessfulType);
			
			// Iterate
			if (IncrementIndices(Types, UntestedIndices)) // Never able to iterate; must be at the end of all possible Type combinations
				break;
			Failsafe2++;
		}

		// Iterate
		if (IncrementIndices(Types, TestedIndices)) // Never able to iterate; must be at the end of all possible Type combinations
			break;
		Failsafe1++;
	}
}
































