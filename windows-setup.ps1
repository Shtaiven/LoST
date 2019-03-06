param (
    [string]$sdl2_zip = "SDL2-devel-2.0.9-VC.zip",
    [string]$sdl2_image_zip = "SDL2_image-devel-2.0.4-VC.zip",
    [switch]$cache = $FALSE
)

# File and folder names
$cache_path = "$($PSScriptRoot)\.windows-setup-cache"
$unzip_path = "$($PSScriptRoot)\SDL2"

# Setup Yes/No choices
$choices = New-Object Collections.ObjectModel.Collection[Management.Automation.Host.ChoiceDescription]
$choices.Add((New-Object Management.Automation.Host.ChoiceDescription -ArgumentList '&Yes'))
$choices.Add((New-Object Management.Automation.Host.ChoiceDescription -ArgumentList '&No'))

# Check for already existing downloads
$sdl2_files = Get-ChildItem -Path $cache_path -Filter "SDL2-*.zip" -ErrorAction SilentlyContinue -Force
$sdl2_image_files = Get-ChildItem -Path $cache_path -Filter "SDL2_image-*.zip" -ErrorAction SilentlyContinue -Force

# Create a new folder for SDL2 libraries
$download = 0
try {
    New-Item -Path $cache_path -ItemType "directory" -ErrorAction Stop | Out-Null
} catch {
    if ($sdl2_files -And $sdl2_image_files) {
        $download = $Host.UI.PromptForChoice("SDL2 libraries already downloaded", "Download again?", $choices, 1)
    }
}

# Download files
if ($download -eq 0) {
    $client = New-Object System.Net.WebClient
    Write-Host "Downloading $($sdl2_zip)"
    $client.DownloadFile("https://www.libsdl.org/release/$($sdl2_zip)", "$($cache_path)\$($sdl2_zip)")
    Write-Host "Downloading $($sdl2_image_zip)"
    $client.DownloadFile("https://www.libsdl.org/projects/SDL_image/release/$($sdl2_image_zip)", "$($cache_path)\$($sdl2_image_zip)")
    $sdl2_files = Get-ChildItem -Path $cache_path -Filter "SDL2-*.zip" -ErrorAction SilentlyContinue -Force
    $sdl2_image_files = Get-ChildItem -Path $cache_path -Filter "SDL2_image-*.zip" -ErrorAction SilentlyContinue -Force
}

# Unzip downloaded files
if ($sdl2_files -And $sdl2_image_files) {
    Remove-Item $unzip_path -Force -Recurse -ErrorAction SilentlyContinue
    Write-Host "Expanding $($sdl2_zip)"
    Expand-Archive -Path "$($cache_path)\$($sdl2_zip)" -DestinationPath $unzip_path -Force
    Write-Host "Expanding $($sdl2_image_zip)"
    Expand-Archive -Path "$($cache_path)\$($sdl2_image_zip)" -DestinationPath $unzip_path -Force
    Write-Host "Consolidating files into $($unzip_path)"
    $expanded = Get-ChildItem -Path $unzip_path -Filter "SDL2*" -ErrorAction SilentlyContinue -Force | ForEach-Object { $_.FullName }
    foreach ($folder in $expanded) {
        Copy-Item -Path "$($folder)\*" -Destination "$($unzip_path)\" -Recurse -Force -ErrorAction SilentlyContinue
        Remove-Item $folder -Force -Recurse -ErrorAction SilentlyContinue
    }
} else {
    Write-Host "SDL2 libraries didn't download. Please try again!"
}

# Clean up
if (!$cache -And $cache_path) {
    Write-Host "Cleaning up"
    Remove-Item $cache_path -Force -Recurse -ErrorAction SilentlyContinue
}

Write-Host "Done"
