/* playwav.c */
#include <alsa/asoundlib.h>
#include <alsa/control.h>
#include <stdio.h>
#include <sndfile.h>

#define PCM_DEVICE "default"

int main(void) {
	snd_pcm_t *pcm_handle;
	snd_pcm_hw_params_t *params;
	snd_pcm_uframes_t frames;
	int dir,pcmrc;
	char *infilename = "Test.wav";
	int* buf=NULL;
	int readcount;
	SF_INFO sfinfo;
	SNDFILE *infile = NULL;
	infile = sf_open(infilename, SFM_READ, &sfinfo);
	fprintf(stderr,"Channels: %d\n", sfinfo.channels); // Channels ist hier 2.
	fprintf(stderr,"Sample rate: %d\n", sfinfo.samplerate); // 44100 bei test.wav
	fprintf(stderr,"Sections: %d\n", sfinfo.sections); 
	fprintf(stderr,"Format: %d\n", sfinfo.format); // PCM (uncompressed),
		16 bit stereo signed
	/* Die Datei auf dem PCM-Gerät im playback mode öffnen */
	snd_pcm_open(&pcm_handle, PCM_DEVICE, SND_PCM_STREAM_PLAYBACK, 0);
	/* erst einmal params mit Standardwerten füllen */
	snd_pcm_hw_params_alloca(&params);
	snd_pcm_hw_params_any(pcm_handle, params);
	/* nun ein paar Parameter verändern */
	snd_pcm_hw_params_set_access(pcm_handle, params,
	SND_PCM_ACCESS_RW_INTERLEAVED);
	snd_pcm_hw_params_set_format(pcm_handle, params, SND_PCM_FORMAT_S32_LE);
	snd_pcm_hw_params_set_channels(pcm_handle, params, sfinfo.channels);
	snd_pcm_hw_params_set_rate(pcm_handle, params, 44100,0);
	/* Parameter neu setzen */
	snd_pcm_hw_params(pcm_handle, params);
	snd_pcm_hw_params_get_period_size(params, &frames, &dir);
	fprintf(stderr,"Frames in einer Zugriffsperiode: %d\n", frames);
	fprintf(stderr,"Starte Audiowiedergabe...\n");
	// Falls das Lesen von frames fehlschlägt, bitte die folgenden 2 Zeilen benutzen:
	// frames=sfinfo.filesize/4; // 16 bit stereo (= 4 Bytes pro Frame)
	// fprintf(stderr,"%d Frames\n",frames);
	buf=malloc(frames*sfinfo.channels*4); // Puffer für Audiodaten anlegen
	while ((readcount=sf_readf_int(infile, buf, frames))>0) { // EOF->readcount=0
		pcmrc = snd_pcm_writei(pcm_handle, buf, readcount);
		if (pcmrc == -EPIPE) {
			fprintf(stderr, "buffer underrun!\n");
			snd_pcm_prepare(pcm_handle);
		}
		else if (pcmrc < 0) {
				fprintf(stderr, "Fehler beim schreiben auf PCM-Gerät: %s\n",
					snd_strerror(pcmrc));
		}
	}
	fprintf(stderr,"Ende der Datei erreicht, schließe Audiogerät\n");
	snd_pcm_drain(pcm_handle);
	snd_pcm_close(pcm_handle);
	free(buf);
	return 0;
}

