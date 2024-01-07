import React, { useCallback } from 'react';
import './assets/scss/main.scss';
import { Route, Routes } from 'react-router-dom';
import { useCookies } from 'react-cookie';
import axios from 'axios';

import Home from './pages/Home';
import Userspage from './pages/Users';
import Callback from './pages/Callback';
import Login from './pages/Login';
import Settings from './pages/Settings';
import Profile from './pages/Profile';
import ProfileId from './pages/ProfileId';
import Chat from './pages/ChatRoom';
import Game from './pages/Game';
import History from './pages/History';
import Game_demo from './pages/Game_demo';
import { ToastContainer } from 'react-toastify';
import 'react-toastify/dist/ReactToastify.css';
import ChatComponent from './Components/ChatComponent';
import Tournament from './pages/Tournament';
import TournamentHistory from './pages/TournamentHistory';

import RouteProtect from './Components/RouteProtect';
import TwoFARouteProtect from './Components/TwoFARouteProtect';

import { MeContext } from './context/MeContext';
import Verify2FA from "./pages/Verify2FA";

function NotFound() {
  return <div className='flex w-screen h-screen justify-center items-center'> 
    <div className= ' bg-gray-500 text-6xl hover:bg-pink-500 text-white px-14 py-10 rounded-2xl h-min'>404 - Page not found</div>
    </div>
}

const App: React.FC = () => {
  const [me, setMe] = React.useState<any>(null);

  return (
    <div className="App flex">
      <Routes>
        <Route path="/login" element={<Login />} />
        <Route path="/game" element={<Game />} />
	  	<Route path="/game_demo" element={<Game_demo />} />
        <Route path="/callback" element={<Callback />} />
        <Route path="/*" element={<NotFound />} />
        <Route path="/verify2fa" element={
          <TwoFARouteProtect>
            <Verify2FA />
          </TwoFARouteProtect>
        } />
        <Route path="/" element={
          <RouteProtect>
            <Home />
          </RouteProtect>
        } />
        <Route path="/users" element={
          <RouteProtect>
            <Userspage />
          </RouteProtect>
        } />
        <Route path="/profile" element={
          <RouteProtect>
            <Profile />
          </RouteProtect>
        } />
        <Route path="/profile/:id" element={
          <RouteProtect>
            <ProfileId />
          </RouteProtect>
        } />
        <Route path="history" element={
          <RouteProtect>
            <History />
          </RouteProtect>
        } />
        <Route path="settings" element={
          <RouteProtect>
            <Settings />
          </RouteProtect>
        } />
        <Route path="/chat/:chatId" Component={ChatComponent} element={
            <RouteProtect>
              <Chat />
            </RouteProtect>
        } />
		<Route path="/tournament" Component={Tournament} element={
			<RouteProtect>
              <Tournament />
            </RouteProtect>
            }/>
		<Route path="/tournamentHistory" Component={TournamentHistory} element={
			<RouteProtect>
              <TournamentHistory />
            </RouteProtect>
            }/>
      </Routes>
      <ToastContainer />
    </div>
  );
};
//TODO see if Component={} is needed
export default App;

