#pragma once
#include "../MessageMain.h"
#include "../responses/ProjectResponses.h"

class GetNumProjectsCmd : public Command {
public:
	GetNumProjectsCmd() : Command(CommandID::GetNumProjects) {}
	void execute() override;

    template <class Archive>
    inline void serialize(Archive& ar, const unsigned int version) {
	    ar& boost::serialization::base_object<Command>(*this);
    }
};

class GetProjectByIndexCmd : public Command {
public:
	A_long proj_indexL;
	GetProjectByIndexCmd() : Command(CommandID::GetProjectByIndex) {}
	GetProjectByIndexCmd(A_long proj_indexL) : proj_indexL(proj_indexL), Command(CommandID::GetProjectByIndex) {}
	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& proj_indexL;
	}
};

class GetProjectNameCmd : public Command {
public:
    AE_Project project;
    GetProjectNameCmd() : Command(CommandID::GetProjectName) {}
    GetProjectNameCmd(AE_Project project) : project(project), Command(CommandID::GetProjectName) {}
    void execute() override;

    template <class Archive>
    inline void serialize(Archive& ar, const unsigned int version) {
	    ar& boost::serialization::base_object<Command>(*this);
	    ar& project;
    }
};

class GetProjectPathCmd : public Command {
public:
	AE_Project project;
	GetProjectPathCmd() : Command(CommandID::GetProjectPath) {}
	GetProjectPathCmd(AE_Project project) : project(project), Command(CommandID::GetProjectPath) {}
	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
	    ar& boost::serialization::base_object<Command>(*this);
	    ar& project;
	}
};

class GetProjectRootFolderCmd : public Command {
public:
	AE_Project project;
	GetProjectRootFolderCmd() : Command(CommandID::GetProjectRootFolder) {}
	GetProjectRootFolderCmd(AE_Project project) : project(project), Command(CommandID::GetProjectRootFolder) {}
	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
	    ar& boost::serialization::base_object<Command>(*this);
	    ar& project;
	}
};

class SaveProjectToPathCmd : public Command {
public:
	AE_Project project;
	std::string pathZ;
	SaveProjectToPathCmd() : Command(CommandID::SaveProjectToPath) {}
	SaveProjectToPathCmd(AE_Project project, std::string pathZ) : project(project), pathZ(pathZ), Command(CommandID::SaveProjectToPath) {}
	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
	    ar& boost::serialization::base_object<Command>(*this);
	    ar& project;
	    ar& pathZ;
	}
};

class GetProjectTimeDisplayCmd : public Command {
public:
	AE_Project project;
	GetProjectTimeDisplayCmd() : Command(CommandID::GetProjectTimeDisplay) {}
	GetProjectTimeDisplayCmd(AE_Project project) : project(project), Command(CommandID::GetProjectTimeDisplay) {}
	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
	    ar& boost::serialization::base_object<Command>(*this);
	    ar& project;
	}
};

class SetProjectTimeDisplayCmd : public Command {
public:
	AE_Project project;
	AEGP_TimeDisplay3 time_display;
	SetProjectTimeDisplayCmd() : Command(CommandID::SetProjectTimeDisplay) {}
	SetProjectTimeDisplayCmd(AE_Project project, AEGP_TimeDisplay3 time_display) : project(project), time_display(time_display), Command(CommandID::SetProjectTimeDisplay) {}
	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
	    ar& boost::serialization::base_object<Command>(*this);
	    ar& project;
	    ar& time_display;
	}
};

class ProjectIsDirtyCmd : public Command {
public:
	AE_Project project;
	ProjectIsDirtyCmd() : Command(CommandID::ProjectIsDirty) {}
	ProjectIsDirtyCmd(AE_Project project) : project(project), Command(CommandID::ProjectIsDirty) {}
	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
	    ar& boost::serialization::base_object<Command>(*this);
	    ar& project;
	}
};

class SaveProjectAsCmd : public Command {
public:
	AE_Project project;
	std::string pathZ;
	SaveProjectAsCmd() : Command(CommandID::SaveProjectAs) {}
	SaveProjectAsCmd(AE_Project project, std::string pathZ) : project(project), pathZ(pathZ), Command(CommandID::SaveProjectAs) {}
	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
	    ar& boost::serialization::base_object<Command>(*this);
	    ar& project;
	    ar& pathZ;
	}
};

class NewProjectCmd : public Command {
public:
	NewProjectCmd() : Command(CommandID::NewProject) {}
	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
	    ar& boost::serialization::base_object<Command>(*this);
	}
};

class OpenProjectFromPathCmd : public Command {
public:
	std::string pathZ;
	OpenProjectFromPathCmd() : Command(CommandID::OpenProjectFromPath) {}
	OpenProjectFromPathCmd(std::string pathZ) : pathZ(pathZ), Command(CommandID::OpenProjectFromPath) {}
	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
	    ar& boost::serialization::base_object<Command>(*this);
	    ar& pathZ;
	}
};

class GetProjectBitDepthCmd : public Command {
public:
	AE_Project project;
	GetProjectBitDepthCmd() : Command(CommandID::GetProjectBitDepth) {}
	GetProjectBitDepthCmd(AE_Project project) : project(project), Command(CommandID::GetProjectBitDepth) {}
	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& project;
	}
};

class SetProjectBitDepthCmd : public Command {
public:
	AE_Project project;
	AEGP_ProjBitDepth bit_depth;
	SetProjectBitDepthCmd() : Command(CommandID::SetProjectBitDepth) {}
	SetProjectBitDepthCmd(AE_Project project, AEGP_ProjBitDepth bit_depth) : project(project), bit_depth(bit_depth), Command(CommandID::SetProjectBitDepth) {}
	void execute() override;

	template <class Archive>
	inline void serialize(Archive& ar, const unsigned int version) {
		ar& boost::serialization::base_object<Command>(*this);
		ar& project;
		ar& bit_depth;
	}
};


