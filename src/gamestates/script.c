/*! \file empty.c
 *  \brief Empty gamestate.
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

#include "../common.h"
#include <stdio.h>
#include <libsuperderpy.h>

struct GamestateResources {
		// This struct is for every resource allocated and used by your gamestate.
		// It gets created on load and then gets passed around to all other function calls.
		char *cur_actor;
		char *cur_emoti;

		char *skip_to;

		bool stopped;
	float f;
	  int anim;

		bool dialog_enabled;
		int dialog_highlight;
		bool speech_jack;

		char *tut_text;

		int selected;

		ALLEGRO_BITMAP *scene;
		ALLEGRO_BITMAP *actor;

		ALLEGRO_FILE *script_file;

		char *script;
		int speech_counter;
		struct Dialog {
			char *text;
			char *script[255];
			int script_length;
			struct Timeline *timeline;
		} dialogs[255];
		int dialog_count;

		int delay;

		char *speech;
		char *status;

		bool dialog_skip;

		int fade;

		ALLEGRO_FONT *font;

		struct Timeline *timeline;

		ALLEGRO_BITMAP *icon;

		int mousex, mousey;
		int mouse_visible;

		ALLEGRO_BITMAP *cursor;

		int prev_selected;

		char* text0;
		char* text1;
		char* text2;
		char* text3;

		bool central;
};

int Gamestate_ProgressCount = 1; // number of loading steps as reported by Gamestate_Load

void Gamestate_Logic(struct Game *game, struct GamestateResources* data) {
	// Called 60 times per second. Here you should do all your game logic.
	  TM_Process(data->timeline);

		/*for (int i=0; i<data->dialog_count; i++) {
		TM_Process(data->dialogs[i].timeline);
	}*/
	if (data->scene) {
		//AnimateCharacter(game, data->scene, 1);
	}
	if (data->mouse_visible) {
		data->mouse_visible--;
	}

}

void Gamestate_Draw(struct Game *game, struct GamestateResources* data) {
	// Called as soon as possible, but no sooner than next Gamestate_Logic call.
	// Draw everything to the screen here.
	//	al_draw_text(data->font, al_map_rgb(255,255,255), game->viewport.width / 2, game->viewport.height / 2,
	    //           ALLEGRO_ALIGN_CENTRE, "Nothing to see here, move along!");

	if (data->scene) {
		//DrawCharacter(game, data->scene, al_map_rgb(255,255,255), 0);
		data->anim++;
		if (data->anim > 5) {
		data->f = rand() / (float)INT_MAX;

		data->f = 0.9 + data->f/10.0;
		data->anim = 0;
		}

		al_draw_tinted_scaled_bitmap(data->scene, al_map_rgba_f(data->f, data->f, data->f, data->f), 0, 0, al_get_bitmap_width(data->scene), al_get_bitmap_height(data->scene),
		                      0,0, game->viewport.width, game->viewport.height, 0);

	}
	if (data->actor) {
		al_draw_scaled_bitmap(data->actor, 0, 0, al_get_bitmap_width(data->actor), al_get_bitmap_height(data->actor),
		                      0,0, game->viewport.width, game->viewport.height, 0);
	}

	/*
	al_draw_filled_rectangle(0, 0, 320, 180, al_map_rgba(0, 0, 0, 255-data->fade));

	if (data->tut_text) {
		al_draw_filled_rectangle(0, 0, 320, 180, al_map_rgba(0, 0, 0, 192));
				DrawWrappedTextWithShadow(data->font, al_map_rgb(255,255,255), 5,  game->viewport.height / 2,
						310, ALLEGRO_ALIGN_CENTRE, data->tut_text);
	}

	if (data->status) {
		al_draw_line(0, 160, 320, 160, al_map_rgb(255,255,255), 3);
		al_draw_filled_rectangle(0, 160, 320, 180, al_map_rgba(0, 0, 0, 192));

		DrawTextWithShadow(data->font, al_map_rgb(255,255,255), game->viewport.width / 2, 167,
				ALLEGRO_ALIGN_CENTRE, data->status);
	}
	if (data->speech) {
		al_draw_line(0, 140, 320, 140, data->speech_jack ? al_map_rgb(255,255,255) : al_map_rgb(255,222,255), 3);
		al_draw_filled_rectangle(0, 140, 320, 180, al_map_rgba(0, 0, 0, 128));
		DrawWrappedText(data->font, data->speech_jack ? al_map_rgb(255,255,255) : al_map_rgb(255,222,255), 5, 145, 310,
				ALLEGRO_ALIGN_LEFT, data->speech);
		if (data->speech_jack) {
			//al_draw_bitmap(data->icon, 2, 140-32, 0);
		}
	}
	if (data->dialog_enabled) {
		al_draw_line(0, 170-((data->dialog_count+1)*10), 320, 170-((data->dialog_count+1)*10), al_map_rgb(255,255,255), 3);
		al_draw_filled_rectangle(0, 170-((data->dialog_count+1)*10), 320, 180, al_map_rgba(0, 0, 0, 192));
		for (int i=0; i<=data->dialog_count; i++) {
			al_draw_text(data->font, (i == data->dialog_highlight) ? al_map_rgb(128,255,255) : al_map_rgb(255,255,255), 5, 175 - (data->dialog_count+1-i)*10,
					ALLEGRO_ALIGN_LEFT, data->dialogs[i].text + 6);
		}
	}
	*/

	if (data->mouse_visible) {
		al_draw_bitmap(data->cursor, data->mousex - 6, data->mousey - 1, 0);
	}

	int leftpos = data->central ? game->viewport.width*0.5 : game->viewport.width*0.3;

	al_draw_text(data->font, al_map_rgb(255,255,255), leftpos, game->viewport.height*0.5 - al_get_font_line_height(data->font) * 2, ALLEGRO_ALIGN_CENTER, data->text0);
	al_draw_text(data->font, al_map_rgb(255,255,255), leftpos, game->viewport.height*0.5 - al_get_font_line_height(data->font) * 0.75, ALLEGRO_ALIGN_CENTER, data->text1);
	al_draw_text(data->font, al_map_rgb(255,255,255), leftpos, game->viewport.height*0.5 + al_get_font_line_height(data->font) * 0.75, ALLEGRO_ALIGN_CENTER, data->text2);
	al_draw_text(data->font, al_map_rgb(255,255,255), leftpos, game->viewport.height*0.5 + al_get_font_line_height(data->font) * 2, ALLEGRO_ALIGN_CENTER, data->text3);

	char status[255];
	snprintf(status, 255, "%f", al_get_audio_stream_position_secs(game->data->music));
	al_draw_text(data->font, al_map_rgb(255,255,255), game->viewport.width*0.5, game->viewport.height*0.9, ALLEGRO_ALIGN_CENTER, status);

}

void Gamestate_ProcessEvent(struct Game *game, struct GamestateResources* data, ALLEGRO_EVENT *ev) {
	// Called for each event in Allegro event queue.
	// Here you can handle user input, expiring timers etc.
	TM_HandleEvent(data->timeline, ev);
	for (int i=0; i<=data->dialog_count; i++) {
		TM_HandleEvent(data->dialogs[i].timeline, ev);
	}
	if ((ev->type==ALLEGRO_EVENT_KEY_DOWN) && (ev->keyboard.keycode == ALLEGRO_KEY_ESCAPE)) {
		  UnloadCurrentGamestate(game); // mark this gamestate to be stopped and unloaded
			LoadGamestate(game, "menu");
			StartGamestate(game, "menu");
		// When there are no active gamestates, the engine will quit.
	}
	if ((ev->type==ALLEGRO_EVENT_KEY_DOWN) && (ev->keyboard.keycode == ALLEGRO_KEY_SPACE)) {
		// When there are no active gamestates, the engine will quit.
	}
	if ((ev->type==ALLEGRO_EVENT_KEY_DOWN) && (ev->keyboard.keycode == ALLEGRO_KEY_FULLSTOP)) {
		data->speech_counter = 0;
		data->delay = 0;
		data->dialog_skip = true;
		TM_SkipDelay(data->timeline);
	}
	if ((ev->type==ALLEGRO_EVENT_KEY_DOWN) && (ev->keyboard.keycode == ALLEGRO_KEY_N)) {
		data->tut_text = NULL;
	}
	if ((ev->type==ALLEGRO_EVENT_KEY_DOWN) && (ev->keyboard.keycode == ALLEGRO_KEY_1)) {
		data->dialog_highlight = 0;
	}
	if ((ev->type==ALLEGRO_EVENT_KEY_DOWN) && (ev->keyboard.keycode == ALLEGRO_KEY_2)) {
		data->dialog_highlight = 1;
	}
	if ((ev->type==ALLEGRO_EVENT_KEY_DOWN) && (ev->keyboard.keycode == ALLEGRO_KEY_3)) {
		data->dialog_highlight = 2;
	}
	if ((ev->type==ALLEGRO_EVENT_KEY_DOWN) && (ev->keyboard.keycode == ALLEGRO_KEY_4)) {
		data->dialog_highlight = 3;
	}

	if ((ev->type==ALLEGRO_EVENT_KEY_UP) && (ev->keyboard.keycode == ALLEGRO_KEY_1)) {
		data->selected = 0;
	}
	if ((ev->type==ALLEGRO_EVENT_KEY_UP) && (ev->keyboard.keycode == ALLEGRO_KEY_2)) {
		data->selected = 1;
	}
	if ((ev->type==ALLEGRO_EVENT_KEY_UP) && (ev->keyboard.keycode == ALLEGRO_KEY_3)) {
		data->selected = 2;
	}
	if ((ev->type==ALLEGRO_EVENT_KEY_UP) && (ev->keyboard.keycode == ALLEGRO_KEY_4)) {
		data->selected = 3;
	}

	if (ev->type==ALLEGRO_EVENT_MOUSE_AXES) {
		data->mousex = (ev->mouse.x / (float)al_get_display_width(game->display)) * game->viewport.width;
		data->mousey = (ev->mouse.y / (float)al_get_display_height(game->display)) * game->viewport.height;
		data->mouse_visible = 180;

		if (data->dialog_enabled) {
			if (data->mousey >= (175 - (data->dialog_count+1)*10)) {
				int y = data->mousey  - (175 - (data->dialog_count+1)*10);
				data->dialog_highlight = y / 10;
			} else {
				data->dialog_highlight = -1;
			}
		}
	}
	if (ev->type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
		if (data->dialog_enabled) {

			data->selected = data->dialog_highlight;
		} else {
			data->speech_counter = 1;
			//data->delay = 1;
			if (data->delay) {
			al_seek_audio_stream_secs(game->data->music, data->delay/100);
			}
			data->delay = 0;
			TM_SkipDelay(data->timeline);
		}
	}
}

bool Speak(struct Game *game, struct TM_Action *action, enum TM_ActionState state) {
	struct GamestateResources *data = TM_GetArg(action->arguments, 0);
	char *text = TM_GetArg(action->arguments, 1);
	bool jack = (bool)TM_GetArg(action->arguments, 2);
	if (state == TM_ACTIONSTATE_START) {
		if (data->skip_to) { return true; }
		data->speech = text + 6;
		data->speech_counter = 60*4;
		data->speech_jack = jack;
		data->dialog_skip = false;
	}
	if (state == TM_ACTIONSTATE_RUNNING) {
		if (data->skip_to) { return true; }
		//ALLEGRO_AUDIO_STREAM *stream = TM_GetArg(action->arguments, 3);
		//if (stream) {
		//	return data->dialog_skip || !al_get_audio_stream_playing(stream);
		//} else {
		  return !(data->speech_counter--);
		//}
	}
	if (state == TM_ACTIONSTATE_DESTROY) {
		data->speech = NULL;
	}
	return true;
}
bool Delay(struct Game *game, struct TM_Action *action, enum TM_ActionState state) {
	struct GamestateResources *data = TM_GetArg(action->arguments, 0);
	char *arg = TM_GetArg(action->arguments, 1);
	if (state == TM_ACTIONSTATE_START) {
		if (data->skip_to) { return true; }
		data->delay = strtoumax(arg, NULL, 10)*60;
	}
	if (state == TM_ACTIONSTATE_RUNNING) {
		if (data->skip_to) { return true; }
		return !(data->delay--);
	}
	return true;
}

bool WaitFor(struct Game *game, struct TM_Action *action, enum TM_ActionState state) {
	struct GamestateResources *data = TM_GetArg(action->arguments, 0);
	char *arg = TM_GetArg(action->arguments, 1);
	if (state == TM_ACTIONSTATE_START) {
		if (data->skip_to) { return true; }
		data->delay = strtoumax(arg, NULL, 10);
	}
	if (state == TM_ACTIONSTATE_RUNNING) {
		if (data->skip_to) { return true; }
		return !(al_get_audio_stream_position_secs(game->data->music) * 100 < data->delay);
	}
	return true;
}


bool Tutorial(struct Game *game, struct TM_Action *action, enum TM_ActionState state) {
	struct GamestateResources *data = TM_GetArg(action->arguments, 0);
	char *text = TM_GetArg(action->arguments, 1);
	if (state == TM_ACTIONSTATE_START) {
		if (data->skip_to) { return true; }
		data->tut_text = text;
	}
	if (state == TM_ACTIONSTATE_RUNNING) {
		if (data->skip_to) { return true; }
		return !data->tut_text;
	}
	return true;
}

bool FadeIn(struct Game *game, struct TM_Action *action, enum TM_ActionState state) {
	struct GamestateResources *data = TM_GetArg(action->arguments, 0);
	if (state == TM_ACTIONSTATE_RUNNING) {
		if (data->skip_to) { return true; }
		data->fade+=3;
		return data->fade >= 255;
	}
	if (state == TM_ACTIONSTATE_DESTROY) {
		data->fade = 255;
	}
	return false;
}
bool FadeOut(struct Game *game, struct TM_Action *action, enum TM_ActionState state) {
	struct GamestateResources *data = TM_GetArg(action->arguments, 0);
	if (state == TM_ACTIONSTATE_RUNNING) {
		if (data->skip_to) { return true; }
		data->fade-=3;
		return data->fade <= 0;
	}
	if (state == TM_ACTIONSTATE_DESTROY) {
		data->fade = 0;
	}
	return false;
}

bool GoTo(struct Game *game, struct TM_Action *action, enum TM_ActionState state) {
	struct GamestateResources *data = TM_GetArg(action->arguments, 0);
	char *name = TM_GetArg(action->arguments, 1);
	if (state == TM_ACTIONSTATE_START) {
		if (data->skip_to) { return true; }
		PrintConsole(game, "jumping to label %s", name);
		data->skip_to = name;
	}
	return true;
}

bool GoToCheck(struct Game *game, struct TM_Action *action, enum TM_ActionState state) {
	struct GamestateResources *data = TM_GetArg(action->arguments, 0);
	char *name = TM_GetArg(action->arguments, 1);
	if (state == TM_ACTIONSTATE_START) {
		if (data->skip_to) { return true; }
		if (data->prev_selected == data->selected) {
			PrintConsole(game, "jumping to label %s", name);
			data->skip_to = name;
		}
	}
	return true;
}


bool Label(struct Game *game, struct TM_Action *action, enum TM_ActionState state) {
	struct GamestateResources *data = TM_GetArg(action->arguments, 0);
	char *name = TM_GetArg(action->arguments, 1);
	if (state == TM_ACTIONSTATE_START) {
		if (!data->skip_to) return true;
		if (strcmp(data->skip_to, name) == 0) {
			PrintConsole(game, "jumped to label %s", name);
			data->skip_to = NULL;
		}
	}
	return true;
}

bool RunScript(struct Game *game, struct TM_Action *action, enum TM_ActionState state) {
	struct GamestateResources *data = TM_GetArg(action->arguments, 0);
	char *name = TM_GetArg(action->arguments, 1);
	if (state == TM_ACTIONSTATE_START) {
		if (data->skip_to) { return true; }
		game->data->script = name;
		UnloadCurrentGamestate(game);
		LoadGamestate(game, "dispatcher");
		StartGamestate(game, "dispatcher");
	}
	return true;
}

bool SetActor(struct Game *game, struct TM_Action *action, enum TM_ActionState state) {
	struct GamestateResources *data = TM_GetArg(action->arguments, 0);
	char *name = TM_GetArg(action->arguments, 1);

	if (state == TM_ACTIONSTATE_INIT) {
		char path[255];

		snprintf(path, 255, "actors/%s-%s.png", name, "on");
		action->arguments = TM_AddToArgs(action->arguments, 1, al_load_bitmap(GetDataFilePath(game, path)));
	}
	if (state == TM_ACTIONSTATE_START) {
		if (data->skip_to) { return true; }
		ALLEGRO_BITMAP *bitmap = TM_GetArg(action->arguments, 2);

		PrintConsole(game, "Setting up actor %s", name);
		if (data->actor) {
			al_destroy_bitmap(data->actor);
		}
		if (data->cur_emoti) {
			free(data->cur_emoti);
		}
		if (data->cur_actor) {
			free(data->cur_actor);
		}
		data->cur_emoti = strdup("on");
		data->cur_actor = strdup(name);
		data->actor = bitmap;
	}
	return true;
}

bool SetEmoti(struct Game *game, struct TM_Action *action, enum TM_ActionState state) {
	struct GamestateResources *data = TM_GetArg(action->arguments, 0);
	char *name = TM_GetArg(action->arguments, 1);

	if (state == TM_ACTIONSTATE_START) {
		if (data->skip_to) { return true; }

		char path[255];

		snprintf(path, 255, "actors/%s-%s.png", data->cur_actor, name);
		ALLEGRO_BITMAP *bitmap = al_load_bitmap(GetDataFilePath(game, path));

		PrintConsole(game, "Setting up emoti %s for actor %s", name, data->cur_actor);
		if (data->actor) {
			al_destroy_bitmap(data->actor);
		}
		if (data->cur_emoti) {
			free(data->cur_emoti);
		}
		data->cur_emoti = strdup(name);
		data->actor = bitmap;
	}
	return true;
}

bool SetScene(struct Game *game, struct TM_Action *action, enum TM_ActionState state) {
	struct GamestateResources *data = TM_GetArg(action->arguments, 0);
	char *name = TM_GetArg(action->arguments, 1);

	if (state == TM_ACTIONSTATE_INIT) {
		char path[255];

		snprintf(path, 255, "scenes/%s.png", name);
		action->arguments = TM_AddToArgs(action->arguments, 1, al_load_bitmap(GetDataFilePath(game, path)));
	}
	if (state == TM_ACTIONSTATE_START) {
		if (data->skip_to) { return true; }
		ALLEGRO_BITMAP *bitmap = TM_GetArg(action->arguments, 2);

		PrintConsole(game, "Setting up scene %s", name);
		if (data->scene) {
			al_destroy_bitmap(data->scene);
		}
		data->scene = bitmap;
	}
	return true;
}



bool StartMusic(struct Game *game, struct TM_Action *action, enum TM_ActionState state) {
	struct GamestateResources *data = TM_GetArg(action->arguments, 0);
	if (state == TM_ACTIONSTATE_START) {
		al_set_audio_stream_playing(game->data->music, true);
	}
	return true;
}

bool PauseMusic(struct Game *game, struct TM_Action *action, enum TM_ActionState state) {
	struct GamestateResources *data = TM_GetArg(action->arguments, 0);
	if (state == TM_ACTIONSTATE_START) {
		al_set_audio_stream_playing(game->data->music, false);
	}
	return true;
}

bool SetCentral(struct Game *game, struct TM_Action *action, enum TM_ActionState state) {
	struct GamestateResources *data = TM_GetArg(action->arguments, 0);
	bool value = TM_GetArg(action->arguments, 1);
	if (state == TM_ACTIONSTATE_START) {
		data->central = value;
	}
	return true;
}

bool SetLine(struct Game *game, struct TM_Action *action, enum TM_ActionState state) {
	struct GamestateResources *data = TM_GetArg(action->arguments, 0);
	char** line = TM_GetArg(action->arguments, 1);
	char* value = TM_GetArg(action->arguments, 2);
	if (state == TM_ACTIONSTATE_START) {
		*line = value;
	}
	return true;
}

bool ExitGame(struct Game *game, struct TM_Action *action, enum TM_ActionState state) {
	struct GamestateResources *data = TM_GetArg(action->arguments, 0);
	if (state == TM_ACTIONSTATE_START) {
		if (data->skip_to) { return true; }
		UnloadCurrentGamestate(game);
		LoadGamestate(game, "menu");
		StartGamestate(game, "menu");
	}
	return true;
}

bool AddDialogOption(struct Game *game, struct TM_Action *action, enum TM_ActionState state) {
	struct GamestateResources *data = TM_GetArg(action->arguments, 0);
	char *arg = TM_GetArg(action->arguments, 1);

	if (state == TM_ACTIONSTATE_START) {
		if (data->skip_to) { return true; }
		data->dialog_count++;
		data->dialogs[data->dialog_count].timeline = TM_Init(game, "dialog-option");
		data->dialogs[data->dialog_count].text = arg;
		TM_AddAction(data->dialogs[data->dialog_count].timeline, Speak, TM_AddToArgs(NULL, 3, data, arg, 1), "Speak");
	}
	return true;
}
void InterpretCommand(struct Game *game, struct GamestateResources* data, struct Timeline *timeline, char* buf);

bool AddDialogSubcommand(struct Game *game, struct TM_Action *action, enum TM_ActionState state) {
	struct GamestateResources *data = TM_GetArg(action->arguments, 0);
	char *arg = TM_GetArg(action->arguments, 1);

	if (state == TM_ACTIONSTATE_START) {
		if (data->skip_to) { return true; }
		InterpretCommand(game, data, data->dialogs[data->dialog_count].timeline, arg);
	}
	return true;
}

bool ExecuteDialogTree(struct Game *game, struct TM_Action *action, enum TM_ActionState state) {
	struct GamestateResources *data = TM_GetArg(action->arguments, 0);
	if (state == TM_ACTIONSTATE_START) {
		if (data->skip_to) { return true; }
		data->selected = -1;
		data->dialog_highlight = -1;
		data->dialog_enabled = true;
	}
	if (state == TM_ACTIONSTATE_RUNNING) {
		if (data->skip_to) { return true; }
		if ((data->selected == -1) || (data->selected > data->dialog_count)) {
			return false;
		} else {
			data->dialog_enabled = false;
		}

		TM_Process(data->dialogs[data->selected].timeline);
		return TM_IsEmpty(data->dialogs[data->selected].timeline);
	}
	if (state == TM_ACTIONSTATE_DESTROY) {
		for (int i=0; i<=data->dialog_count; i++) {
			TM_Destroy(data->dialogs[i].timeline);
		}
		data->dialog_count = -1;
		data->prev_selected = data->selected;
	}
	return false;
}

void InterpretCommand(struct Game *game, struct GamestateResources* data, struct Timeline *timeline, char* buf) {
	char *cmd = strdup(buf);
	if ((!cmd[0]) || (cmd[0]=='-') || (cmd[0] == '\n')) {
		return;
	}
	cmd[5] = '\0';
	char *arg = NULL;
	if (strlen(buf) > 6) {
		arg = cmd + 6;
		if (arg[strlen(arg)-1] == '\n') {
			arg[strlen(arg)-1] = 0;
		}
	}
	if (strcmp(cmd, "ACTOR") == 0) {
		TM_AddAction(timeline, SetActor, TM_AddToArgs(NULL, 2, data, arg), "SetActor");
	} else if (strcmp(cmd, "SCENE") == 0) {
		TM_AddAction(timeline, SetScene, TM_AddToArgs(NULL, 2, data, arg), "SetScene");
	} else if (strcmp(cmd, "DELAY") == 0) {
		TM_AddAction(timeline, Delay, TM_AddToArgs(NULL, 2, data, arg), "Delay");

		//TM_AddDelay(data->timeline, strtoumax(arg, NULL, 10)*60);
	} else if (strcmp(cmd, "SAYAC") == 0) {
		PrintConsole(game, "say actor");
		TM_AddAction(timeline, Speak, TM_AddToArgs(NULL, 3, data, arg, 0), "Speak");
	} else if (strcmp(cmd, "SAYJK") == 0) {
		PrintConsole(game, "say jack");
		TM_AddAction(timeline, Speak, TM_AddToArgs(NULL, 3, data, arg, 1), "Speak");
	} else if (strcmp(cmd, "FADEI") == 0) {
		TM_AddAction(timeline, FadeIn, TM_AddToArgs(NULL, 1, data), "FadeIn");
	} else if (strcmp(cmd, "FADEO") == 0) {
		TM_AddAction(timeline, FadeOut, TM_AddToArgs(NULL, 1, data), "FadeOut");
	} else if (strcmp(cmd, "EVIDE") == 0) {
		PrintConsole(game, "evidence");
//		TM_AddAction(timeline, ShowEvidence, TM_AddToArgs(NULL, 2, data, arg), "ShowEvidence");
	} else if (strcmp(cmd, "DIALO") == 0) {
		PrintConsole(game, "dialog tree");
		TM_AddAction(timeline, AddDialogOption, TM_AddToArgs(NULL, 2, data, arg), "AddDialogOption");
	} else if (strcmp(cmd, "  CMD") == 0) {
		PrintConsole(game, "  -- subcommand");
		TM_AddAction(timeline, AddDialogSubcommand, TM_AddToArgs(NULL, 2, data, arg), "AddDialogSubcommand");
	} else if (strcmp(cmd, "RUND!") == 0) {
		PrintConsole(game, "RUN dialog tree!");
		TM_AddAction(timeline, ExecuteDialogTree, TM_AddToArgs(NULL, 1, data), "ExecuteDialogTree");

	} else if (strcmp(cmd, "TUTOR") == 0) {
		PrintConsole(game, "tutorial block");
		TM_AddAction(timeline, Tutorial, TM_AddToArgs(NULL, 2, data, arg), "Tutorial");

	} else if (strcmp(cmd, "GOTO!") == 0) {
		PrintConsole(game, "GO TO");
		TM_AddAction(timeline, GoTo, TM_AddToArgs(NULL, 2, data, arg), "GoTo");

	} else if (strcmp(cmd, "CHECK") == 0) {
		PrintConsole(game, "GO TO IF SAME");
		TM_AddAction(timeline, GoToCheck, TM_AddToArgs(NULL, 2, data, arg), "GoToCheck");

	} else if (strcmp(cmd, "EMOTI") == 0) {
		TM_AddAction(timeline, SetEmoti, TM_AddToArgs(NULL, 2, data, arg), "SetEmoti");
	} else if (strcmp(cmd, "LABEL") == 0) {
		PrintConsole(game, "label achieved");
		TM_AddAction(timeline, Label, TM_AddToArgs(NULL, 2, data, arg), "Label");

	} else if (strcmp(cmd, "SCRIP") == 0) {
		PrintConsole(game, "switch to script");
		TM_AddAction(timeline, RunScript, TM_AddToArgs(NULL, 2, data, arg), "Script");
	}  else if (strcmp(cmd, "NOTES") == 0) {
		PrintConsole(game, "sum up the game");
//		TM_AddAction(timeline, NotebookOverview, TM_AddToArgs(NULL, 1, data), "NotebookOverview");
	} else if (strcmp(cmd, "CLOSE") == 0) {
		PrintConsole(game, "close the game");
		TM_AddAction(timeline, ExitGame, TM_AddToArgs(NULL, 1, data), "Exit");

	} else if (strcmp(cmd, "LINE0") == 0) {
		TM_AddAction(timeline, SetLine, TM_AddToArgs(NULL, 3, data, &data->text0, arg), "Line0");
	} else if (strcmp(cmd, "LINE1") == 0) {
		TM_AddAction(timeline, SetLine, TM_AddToArgs(NULL, 3, data, &data->text1, arg), "Line1");
	} else if (strcmp(cmd, "LINE2") == 0) {
		TM_AddAction(timeline, SetLine, TM_AddToArgs(NULL, 3, data, &data->text2, arg), "Line2");
	} else if (strcmp(cmd, "LINE3") == 0) {
		TM_AddAction(timeline, SetLine, TM_AddToArgs(NULL, 3, data, &data->text3, arg), "Line3");
	} else if (strcmp(cmd, "SETLC") == 0) {
		TM_AddAction(timeline, SetCentral, TM_AddToArgs(NULL, 2, data, 1), "Central");
	} else if (strcmp(cmd, "SETLL") == 0) {
		TM_AddAction(timeline, SetCentral, TM_AddToArgs(NULL, 2, data, 0), "Left");
	} else if (strcmp(cmd, "START") == 0) {
		TM_AddAction(timeline, StartMusic, TM_AddToArgs(NULL, 1, data), "StartMusic");
	} else if (strcmp(cmd, "PAUSE") == 0) {
		TM_AddAction(timeline, PauseMusic, TM_AddToArgs(NULL, 1, data), "PauseMusic");
	} else if (strcmp(cmd, "WAITF") == 0) {
		TM_AddAction(timeline, WaitFor, TM_AddToArgs(NULL, 2, data, arg), "WaitFor");
	} else if (strcmp(cmd, "CLEAR") == 0) {
		TM_AddAction(timeline, SetLine, TM_AddToArgs(NULL, 3, data, &data->text0, arg), "Line0");
		TM_AddAction(timeline, SetLine, TM_AddToArgs(NULL, 3, data, &data->text1, arg), "Line1");
		TM_AddAction(timeline, SetLine, TM_AddToArgs(NULL, 3, data, &data->text2, arg), "Line2");
		TM_AddAction(timeline, SetLine, TM_AddToArgs(NULL, 3, data, &data->text3, arg), "Line3");
	}
	else {
		FatalError(game, false, "UNRECOGNIZED COMMAND %s", buf);
	}
}

void* Gamestate_Load(struct Game *game, void (*progress)(struct Game*)) {
	// Called once, when the gamestate library is being loaded.
	// Good place for allocating memory, loading bitmaps etc.
	struct GamestateResources *data = calloc(1, sizeof(struct GamestateResources)); // everything is NULL at this point

	data->font = al_load_font(GetDataFilePath(game, "fonts/DejaVuSansMono.ttf"), game->viewport.height * 0.04, 0);

	char path[255];
	snprintf(path, 255, "scripts/%s.sd", game->data->script);
	data->script_file = al_fopen(GetDataFilePath(game, path), "r");
	data->icon = al_load_bitmap(GetDataFilePath(game, GetGameName(game, "icons/%s.png")));
	data->cursor = al_load_bitmap(GetDataFilePath(game, "cursor.png"));

	data->timeline = TM_Init(game, "script");

	do {
		char buf[255];
		al_fgets(data->script_file, buf, 255);
		InterpretCommand(game, data, data->timeline, buf);
	}	while (!al_feof(data->script_file));

	progress(game); // report that we progressed with the loading, so the engine can draw a progress bar
	return data;
}

void Gamestate_Unload(struct Game *game, struct GamestateResources* data) {
	// Called when the gamestate library is being unloaded.
	// Good place for freeing all allocated memory and resources.
	al_destroy_font(data->font);
	al_fclose(data->script_file);
	TM_Destroy(data->timeline);
	if (data->scene) {
		al_destroy_bitmap(data->scene);
	}
	if (data->actor) {
		al_destroy_bitmap(data->actor);
	}
	if (data->cur_emoti) {
		free(data->cur_emoti);
	}
	if (data->cur_actor) {
		free(data->cur_actor);
	}
	al_destroy_bitmap(data->icon);
	al_destroy_bitmap(data->cursor);
	free(data);
}

void Gamestate_Start(struct Game *game, struct GamestateResources* data) {
	// Called when this gamestate gets control. Good place for initializing state,
	// playing music etc.
	data->dialog_count = -1;

	data->text0 = "";
	data->text1 = "";
	data->text2 = "";
	data->text3 = "";

	/*data->speech = "Spicz";
	data->status = "Ewidens";
	data->dialog_count = 4;
	data->dialogs[0] = (struct Dialog){.text = "lala1"};
	data->dialogs[1] = (struct Dialog){.text = "lala2"};
	data->dialogs[2] = (struct Dialog){.text = "lala3"};
	data->dialogs[3] = (struct Dialog){.text = "lala4"};*/


}

void Gamestate_Stop(struct Game *game, struct GamestateResources* data) {
	// Called when gamestate gets stopped. Stop timers, music etc. here.
}

void Gamestate_Pause(struct Game *game, struct GamestateResources* data) {
	// Called when gamestate gets paused (so only Draw is being called, no Logic not ProcessEvent)
	// Pause your timers here.
}

void Gamestate_Resume(struct Game *game, struct GamestateResources* data) {
	// Called when gamestate gets resumed. Resume your timers here.
}

// Ignore this for now.
void Gamestate_Reload(struct Game *game, struct GamestateResources* data) {}
