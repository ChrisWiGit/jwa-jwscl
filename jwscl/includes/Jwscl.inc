{**************************************************************************************************}
{                                                                                                  }
{  The contents of this file are subject to the Mozilla Public License Version 1.1 (the "License");}
{  you may not use this file except in compliance with the License. You may obtain a copy of the   }
{  License at http://www.mozilla.org/MPL/                                                          }
{                                                                                                  }
{  Software distributed under the License is distributed on an "AS IS" basis, WITHOUT WARRANTY OF  }
{  ANY KIND, either express or implied. See the License for the specific language governing rights }
{  and limitations under the License.                                                              }
{                                                                                                  }
{  The Original Code is: jwscl.inc.                                                                }
{  The Initial Developer of the Original Code is Project JEDI http://www.delphi-jedi.org           }
{                                                                                                  }
{  Alternatively, the contents of this file may be used under the terms of the GNU Lesser General  }
{  Public License (the  "LGPL License"), in which case the provisions of the LGPL License are      }
{  applicable instead of those above. If you wish to allow use of your version of this file only   }
{  under the terms of the LGPL License and not to allow others to use your version of this file    }
{  under the MPL, indicate your decision by deleting the provisions above and replace them with    }
{  the notice and other provisions required by the LGPL License. If you do not delete the          }
{  provisions above, a recipient may use your version of this file under either the MPL or the     }
{  LGPL License.                                                                                   }
{                                                                                                  }
{  For more information about the LGPL: http://www.gnu.org/copyleft/lesser.html                    }
{                                                                                                  }
{**************************************************************************************************}
{                                                                                                  }
{  Jedi Windows Security Code Library Header File                                                  }
{  This file defines various generic compiler directives used in JWSCL.                            }
{                                                                                                  }
{**************************************************************************************************}
{                                                                                                  }
{ Last modified: $Date:: 2010-09-21 21:08:33 +0000 (Tue, 21 Sep 2010)                            $ }
{ Revision:      $Rev:: 1019                                                                     $ }
{ Author:        $Author:: dezipaitor                                                            $ }
{ URL:           $HeadURL:: file:///svn/p/jedi-apilib/code/jwscl/trunk/includes/Jwscl.inc        $ }
{                                                                                                  }
{**************************************************************************************************}



//Freepascal compability mode (not fully supported)
{.$DEFINE FPC}

//use JEDI Component Library
{.$DEFINE JCL}

{Activate VISTA and newer functions calls.
If this definition is set and the application is compiled with
static linked jwaVista.pas the binary application will fail
on pre Vista Windows versions!!

Warning: Unsetting this value will not remove constructor, method and property
definitions created for Windows Vista. It only removes function calls
so that static linked apps will not fail immediately on pre Vista systems.
Of course they will fail if Vista stuff is called on them.

Warning #2: If the JEDI API headers are used with a directive WIN_XP or lower
  this switch must be unset.
  These compiler directives reside in includes\jediapilib.inc
  Use at least WINVISTA or WIN2008
}
{$DEFINE VISTA}

//adds compiler version directives
//jwscl.inc is only added by JWSCL units in source folder
//so we're actually in the source folder and must jump up

//This is for compability reasons only!
//On of them should work. However the second one is standard and supported.

//JediAPILib.inc is included from an external svn repo
//Infact this repo is the JEDI API svn repo which
//contains includes\JediAPILib.inc . So there it points to.
//If this does not work, you forgot to add \jwscl\trunk\source to your LIBRARY path.
{$I ..\includes\jwa\JediAPILib.inc}



{$IFDEF FPC}
{$mode delphi}{.$H+}
{$ENDIF}

{$IFDEF DEBUG}
//
//Adds stack trace (using JCL) to JWSCL exceptions
{.$DEFINE JWSCL_DEBUG_INFO}
{$ENDIF DEBUG}

//Use cache mechanism for
// * TJwSecurityID.GetAccountSidString and property AccountName
{.$DEFINE JWSCL_USE_CACHES}

//Define this switch to allow showing a JWSCL task dialog when an exception is raised.
//In this way the default Delphi exception dialog is replaced.
//However, the VCL exception handling is not catched though. Instead, read the
//documentation of JwsclException.pas::JwHandleJwsclException and find out
//how to show the JWSCL dialog with VCL.
//The task dialog is only shown if the JEDI API source was compiled with compiler switch
//WIN2008 or WINVISTA and the running system is a Vista/2008 or newer.
{.$DEFINE JWSCL_USE_TASK_EXCEPTION_DIALOGS}

{$IFDEF JWSCL_USE_CACHES}
  {$DEFINE JWSCL_SIDCACHE}
{$ENDIF JWSCL_USE_CACHES}

//If JWSCL_TYPEINFO is set, JWSCL uses the unit TypInfo
//See JWSCLUtils.pas GetUnitName
{.$DEFINE JWSCL_TYPEINFO}


{$IFDEF DELPHI2010_UP}
{$IFNDEF DEBUG}
  //Remove RTTI information for all JWSCL classes
  //D2010 adds it though
  {$RTTI EXPLICIT METHODS([]) PROPERTIES([]) FIELDS([])}
{$ENDIF DEBUG}
{$ENDIF DELPHI2010_UP}

{$IFDEF DEBUG}
  {.$WARNINGS OFF}
{$IFDEF DELPHI7_UP}
  {$WARN GARBAGE OFF} //removes warning about code behind end.
{$ENDIF DELPHI7_UP}
{$ENDIF DEBUG}

//Remove range check errors since we are using
//variable length structures (like PSID) that fool Delphi
//See: http://stackoverflow.com/questions/1913460/delphi-rangecheckerror-in-jedi-wscl/1914245
{$R-}

//If this compiler directive is set, the JWSCL exception EJwsclProcNotFound will
//correspond to EJwaGetProcAddressError; otherwise EExternalException .
//This is necessary if the JWA functions are loaded dynamically and a function
//is not available in the current Windows version. In this case JWA throws
//EJwaGetProcAddressError.
//However, in case of JWA is compiled with Delphi delayed feature, Delphi will
//throw an EExternalException.
//In this way JWSCL doesn't need to check everywhere for both exception types.
//
//If you don't like to use EExternalException you can activate JWSCL_USE_DELAYED.
{$DEFINE JWSCL_PROCNOTFOUND_EXCEPTION}

//JWSCL can hook the Delphi delayed feature, so in case of errors the exception EExternalException
//is converted to EJwaGetProcAddressError or EJwaLoadLibraryError.
//To allow JWSCL to hook the delayed feature, you need to call JwsclExceptions.pas::JwInitDelayedFunctionHook
//This call should be in a unit that is included on top of your uses clause in your main project file.
//This feature is available in Delphi2010 and newer only
{$IFDEF DELPHI2010_UP}
  {$DEFINE JWSCL_USE_DELAYED}
{$ENDIF DELPHI2010_UP}

//Uses taskdialog when a JWSCL exception occurs in Delphi
//This needs Vista or newer and a manifest specifying Common Control Version 6 (or newer)
//<code>
//     <dependency>
//        <dependentAssembly>
//            <assemblyIdentity
//                type="win32"
//                name="Microsoft.Windows.Common-Controls"
//                version="6.0.0.0"
//                processorArchitecture="*"
//                publicKeyToken="6595b64144ccf1df"
//                language="*"
//        />
//        </dependentAssembly>
//    </dependency>
//</code>
//
//
{$DEFINE JWSCL_USE_TASK_EXCEPTION_DIALOGS}

// If JWSCL_LOCAL_SAFE_LOAD_LIBRARY is set
//   TJwLibraryUtilities.LoadLibProc will load libraries in a safe way.
// Furthermore the function TJwLibraryUtilities.EnterSafeLoadLibrary will be enabled.
// In this way the current directory will be set to the system directory.
{$DEFINE JWSCL_LOCAL_SAFE_LOAD_LIBRARY}

// If JWSCL_GLOBAL_SAFE_LOAD_LIBRARY is set
//  the unit initialization JwsclProcess will call TJwLibraryUtilities.SecureDLLSearchPath;
// and secure all calls to LoadLibrary and CreateProcess
//  I.e. the current directory and the process directory will be searched last for exe, dll, sys and
//    such after system dirs. The current folder of process will be set to the system directory.
//
// JWSCL_LOCAL_SAFE_LOAD_LIBRARY makes define JWSCL_LOCAL_SAFE_LOAD_LIBRARY unnecessary.
//
// You can call TJwLibraryUtilities.SecureDLLSearchPath; manually which should be done as early as possible
//   and in favour of this definition.
{.$DEFINE JWSCL_GLOBAL_SAFE_LOAD_LIBRARY}

//This include must be at the end of include definitions
//If this does not work, you forgot to add jwscl source folder to your LIBRARY path.
{$INCLUDE ..\includes\jwsclAdditionals.inc}

//the following line must be at the end of this file!!
{Warning: This line is printed because an identifier has no pasdoc comment. This error must be fixed.}
