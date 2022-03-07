%----------------------------------------------------------------------------
% GNU Octave / MatLab script file
% Daniel J. Greenhoe
% Usage of this file:
%   (1) Open Octave command prompt
%   (2) At prompt, change to this directory: cd <this directory>
%   (3) Execute this script: AudioData
%   (4) Locate output file AudioData.h in <this directory>
%----------------------------------------------------------------------------

clear;
printf(" ============================================================ \n");
printf("| Utility for converting from Audacity generated .mat file   |\n");
printf("|   to const uint16_t typed array in file AudioData.h        |\n");
printf(" ============================================================ \n");

x = load('Audio_float64bit.mat');
fieldnames(x)
SampleRate = x.samplerate;
Ydata      = x.wavedata;
Ymean      = mean(Ydata);
Yzeromean  = Ydata - Ymean;
Yfullscale = Yzeromean / max(Yzeromean);
Yfixed16   = round((Yfullscale + 1.0) * 0.5 * 0x0FFF);
NumSamples = length(Yfixed16);

FileID = fopen( 'AudioData.h', 'w' );
fprintf( FileID, "uint16_t const AudioData[ ] =\n" );
fprintf( FileID, "{\n  " );
for n = 1:NumSamples
  fprintf( FileID, "0x%04X, ", Yfixed16(n) );
  if( mod(n,16)==0 ) fprintf(FileID, "\n  " ); end
end
fprintf(FileID, "\n};\n" );
fclose( FileID );

