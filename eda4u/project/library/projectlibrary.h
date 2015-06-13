/*
 * EDA4U - Professional EDA for everyone!
 * Copyright (C) 2013 Urban Bruhin
 * http://eda4u.ubruhin.ch/
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef PROJECT_PROJECTLIBRARY_H
#define PROJECT_PROJECTLIBRARY_H

/*****************************************************************************************
 *  Includes
 ****************************************************************************************/

#include <QtCore>
#include <eda4ucommon/exceptions.h>
#include <eda4ucommon/fileio/filepath.h>

/*****************************************************************************************
 *  Forward Declarations
 ****************************************************************************************/

namespace project {
class Project;
}

namespace library {
class Symbol;
class Footprint;
class Model3D;
class SpiceModel;
class Package;
class GenericComponent;
class Component;
}

/*****************************************************************************************
 *  Class ProjectLibrary
 ****************************************************************************************/

namespace project {

/**
 * @brief The ProjectLibrary class
 */
class ProjectLibrary final : public QObject
{
        Q_OBJECT

    public:

        // Constructors / Destructor
        explicit ProjectLibrary(Project& project, bool restore, bool readOnly) throw (Exception);
        ~ProjectLibrary() noexcept;

        // Getters: Library Elements
        const QHash<QUuid, const library::Symbol*>&             getSymbols()            const noexcept {return mSymbols;}
        const QHash<QUuid, const library::Footprint*>&          getFootprints()         const noexcept {return mFootprints;}
        const QHash<QUuid, const library::Model3D*>&            getModels()             const noexcept {return mModels;}
        const QHash<QUuid, const library::SpiceModel*>&         getSpiceModels()        const noexcept {return mSpiceModels;}
        const QHash<QUuid, const library::Package*>&            getPackages()           const noexcept {return mPackages;}
        const QHash<QUuid, const library::GenericComponent*>&   getGenericComponents()  const noexcept {return mGenericComponents;}
        const QHash<QUuid, const library::Component*>&          getComponents()         const noexcept {return mComponents;}
        const library::Symbol*           getSymbol(     const QUuid& uuid) const noexcept;
        const library::Footprint*        getFootprint(  const QUuid& uuid) const noexcept;
        const library::Model3D*          getModel(      const QUuid& uuid) const noexcept;
        const library::SpiceModel*       getSpiceModel( const QUuid& uuid) const noexcept;
        const library::Package*          getPackage(    const QUuid& uuid) const noexcept;
        const library::GenericComponent* getGenComp(    const QUuid& uuid) const noexcept;
        const library::Component*        getComponent(  const QUuid& uuid) const noexcept;


    private:

        // make some methods inaccessible...
        ProjectLibrary();
        ProjectLibrary(const ProjectLibrary& other);
        ProjectLibrary& operator=(const ProjectLibrary& rhs);

        // Private Methods
        template <typename ElementType>
        void loadElements(const FilePath& directory, const QString& type,
                          QHash<QUuid, const ElementType*>& elementList) throw (Exception);

        // General
        Project& mProject; ///< a reference to the Project object (from the ctor)
        FilePath mLibraryPath; ///< the "lib" directory of the project

        // The Library Elements
        QHash<QUuid, const library::Symbol*> mSymbols;
        QHash<QUuid, const library::Footprint*> mFootprints;
        QHash<QUuid, const library::Model3D*> mModels;
        QHash<QUuid, const library::SpiceModel*> mSpiceModels;
        QHash<QUuid, const library::Package*> mPackages;
        QHash<QUuid, const library::GenericComponent*> mGenericComponents;
        QHash<QUuid, const library::Component*> mComponents;

};

} // namespace project

#endif // PROJECT_PROJECTLIBRARY_H