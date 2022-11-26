import { Middleware, Action, Dispatch } from "@reduxjs/toolkit";
import actions from "./warningsActions";
import { RootState } from "renderer/project/store/configureStore";
import { backgroundSelectors } from "renderer/project/store/features/entities/entitiesState";
import API from "renderer/lib/api";

const warningsMiddleware: Middleware<Dispatch, RootState> =
  (store) => (next) => (action: Action) => {
    if (actions.checkBackgroundWarnings.match(action)) {
      const state = store.getState();
      const backgroundsLookup = backgroundSelectors.selectEntities(state);
      const background = backgroundsLookup[action.payload.backgroundId];
      const projectRoot = state.document.root;

      if (background) {
        const cachedWarnings =
          state.warnings.backgrounds[action.payload.backgroundId];
        if (
          !cachedWarnings ||
          cachedWarnings.timestamp < background._v ||
          cachedWarnings.is360 !== action.payload.is360
        ) {
          API.project
            .getBackgroundInfo(background, action.payload.is360, projectRoot)
            .then((info) => {
              store.dispatch(
                actions.setBackgroundWarnings({
                  id: action.payload.backgroundId,
                  is360: action.payload.is360,
                  warnings: info.warnings,
                  numTiles: info.numTiles,
                })
              );
            });
        }
      }
    }
    return next(action);
  };

export default warningsMiddleware;
