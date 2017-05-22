// Copyright (c) 2016-2017 Codice Software - Sebastien Rombauts (sebastien.rombauts@gmail.com)

#pragma once

#include "CoreMinimal.h"
#include "ISourceControlState.h"
#include "PlasticSourceControlRevision.h"

namespace EWorkspaceState
{
	enum Type
	{
		Unknown,
		Ignored,
		Controlled, // called "Pristine" in Perforce, "Unchanged" in Git, "Clean" in SVN
		CheckedOut,
		Added,
		Moved, // Renamed
		Copied,
		Replaced, // Replaced / Merged
		Deleted,
		LocallyDeleted, // Missing
		Changed, // Modified but not CheckedOut
		Conflicted,
		LockedByOther, // LockedBy with name of someone else than cm whoami
		Private, // "Not Controlled"/"Not In Depot"/"Untracked"
	};

	// debug log utility
	const TCHAR* ToString(EWorkspaceState::Type InWorkspaceState);
}

class FPlasticSourceControlState : public ISourceControlState, public TSharedFromThis<FPlasticSourceControlState, ESPMode::ThreadSafe>
{
public:
	FPlasticSourceControlState( const FString& InLocalFilename )
		: LocalFilename(InLocalFilename)
		, WorkspaceState(EWorkspaceState::Unknown)
		, DepotRevisionChangeset(-1)
		, LocalRevisionChangeset(-1)
		, TimeStamp(0)
	{
	}

	// debug log utility
	const TCHAR* ToString() const
	{
		return EWorkspaceState::ToString(WorkspaceState);
	}

	/** ISourceControlState interface */
	virtual int32 GetHistorySize() const override;
	virtual TSharedPtr<class ISourceControlRevision, ESPMode::ThreadSafe> GetHistoryItem(int32 HistoryIndex) const override;
	virtual TSharedPtr<class ISourceControlRevision, ESPMode::ThreadSafe> FindHistoryRevision(int32 RevisionNumber) const override;
	virtual TSharedPtr<class ISourceControlRevision, ESPMode::ThreadSafe> FindHistoryRevision(const FString& InRevision) const override;
	virtual TSharedPtr<class ISourceControlRevision, ESPMode::ThreadSafe> GetBaseRevForMerge() const override;
	virtual FName GetIconName() const override;
	virtual FName GetSmallIconName() const override;
	virtual FText GetDisplayName() const override;
	virtual FText GetDisplayTooltip() const override;
	virtual const FString& GetFilename() const override;
	virtual const FDateTime& GetTimeStamp() const override;
	virtual bool CanCheckIn() const override;
	virtual bool CanCheckout() const override;
	virtual bool IsCheckedOut() const override;
	virtual bool IsCheckedOutOther(FString* Who = nullptr) const override;
	virtual bool IsCurrent() const override;
	virtual bool IsSourceControlled() const override;
	virtual bool IsAdded() const override;
	virtual bool IsDeleted() const override;
	virtual bool IsIgnored() const override;
	virtual bool CanEdit() const override;
	virtual bool CanDelete() const; // override; // commented out for UE4.12 and 4.13 compatibility : method added for 4.14
	virtual bool IsUnknown() const override;
	virtual bool IsModified() const override;
	virtual bool CanAdd() const override;
	virtual bool IsConflicted() const override;

public:
	/** History of the item, if any */
	TPlasticSourceControlHistory History;

	/** Filename on disk */
	FString LocalFilename;

	/** Relative filename of the file in merge conflict */
	FString PendingMergeFilename;

	/** Changeset with which our local revision diverged from the source/remote revision */
	int32 PendingMergeBaseChangeset;

	/** Changeset of the source/remote revision of the merge in progress */
	int32 PendingMergeSourceChangeset;

	/** Plastic SCM Parameters of the merge in progress */
	TArray<FString> PendingMergeParameters;

	/** If a user (another or ourself) has this file locked, this contains his name. */
	FString LockedBy;

	/** Location of the locked file. */
	FString LockedWhere;

	/** State of the workspace */
	EWorkspaceState::Type WorkspaceState;

	/** Latest revision number of the file in the depot */
	int DepotRevisionChangeset;

	/** Latest revision number at which a file was synced to before being edited */
	int LocalRevisionChangeset;

	/** Whether the file is a binary file or not */
//	bool bBinary;

	/** The timestamp of the last update */
	FDateTime TimeStamp;
};
