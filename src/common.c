/*! \file common.c
 *  \brief Common stuff that can be used by all gamestates.
 */
/*
 * Copyright (c) Sebastian Krzyszkowiak <dos@dosowisko.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include "common.h"
#include <stdio.h>
#include <libsuperderpy.h>

struct CommonResources* CreateGameData(struct Game *game) {
	struct CommonResources *data = calloc(1, sizeof(struct CommonResources));
	data->script = "akt1";

//	data->music = al_load_audio_stream(GetDataFilePath(game, "music.ogg"), 4, 1024);
//	al_set_audio_stream_playing(data->music, false);
//	al_attach_audio_stream_to_mixer(data->music, game->audio.music);

	//al_set_audio_stream_speed(data->music, 2);

	return data;
}

void DestroyGameData(struct Game *game, struct CommonResources *data) {
	free(data);
}
