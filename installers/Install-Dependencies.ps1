param (
    [Parameter(Mandatory=$false)][string]$CmakeVersion = "3.24.0",
    [Parameter(Mandatory=$false)][string]$WinPcapDownloadURL = "https://www.winpcap.org/install/bin/WpdPack_4_1_2.zip"
)



function Install-CMake {
    $exePath = "$($env:TEMP)\cmake.exe"

    if ($(Test-Path -Path $exePath)) {
        Remove-Item -Path $exePath
    }

    Invoke-WebRequest -Uri "https://github.com/Kitware/CMake/releases/download/v$($cmakeVersion)/cmake-$($cmakeVersion)-windows-x86_64.msi" -UseBasicParsing -OutFile $exePath
    Start-Process msiexec.exe -ArgumentList "/i $exePath ADD_CMAKE_TO_PATH=Machine /qn" -Wait

    # Reimport Env-Variables
    foreach($level in "Machine","User") {
        [Environment]::GetEnvironmentVariables($level).GetEnumerator() | % {
        # For Path variables, append the new values, if they're not already in there
        if($_.Name -match 'Path$') { 
            $_.Value = ($((Get-Content "Env:$($_.Name)") + ";$($_.Value)") -split ';' | Select-Object -unique) -join ';'
        }
        $_
        } | Set-Content -Path { "Env:$($_.Name)" }
    }

    Write-Host "CMAKE-VERSION: $(cmake --version)"
}

function Install-WinPcapDevPack {
    $zipFileName = $WinPcapDownloadURL.Split('/')[-1]
    $zipFilePath = "..\libs\$($zipFileName)"

    Invoke-WebRequest -Uri $WinPcapDownloadURL -OutFile $zipFilePath
    Expand-Archive $zipFilePath -DestinationPath "..\libs\WinPcap"
}

function Install-Libtins {
    $libDir = "..\libs\libtins"
    $cwd = "$($PWD.Path)"

    Set-Location -Path $env:TEMP # funktioniert nur wenn das script/command von goblib/.dependencies/installers/windows ausgeführt wird!!

    git clone https://github.com/mfontanini/libtins.git $libDir

    Set-Location -Path $libDir
    New-Item -Path "$($libDir)\build" -ItemType Directory
    Set-Location -Path "$($libDir)\build"

    cmake ../ -DPCAP_ROOT_DIR="..\libs\WinPcap" -DLIBTINS_ENABLE_WPA2=1 -DLIBTINS_BUILD_SHARED=0
    cmake --build .

    Set-Location -Path $cwd
}

if ("$($PWD.Path)" -match "^.*\\installers$") {
    Install-CMake
    Install-WinPcapDevPack
    Install-Libtins
}
else {
    Write-Host "NOT ON INSTALLER PATH"
}