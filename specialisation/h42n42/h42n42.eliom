
(* SHARED SIDE *)
[%%shared
open Eliom_lib
open Eliom_content
open Html.D
open Js_of_ocaml

]

(* CLIENT SIDE *)
[%%client
open Eliom_lib
open Eliom_content
open Html.D
open Js_of_ocaml
open Js_of_ocaml_lwt
open Lwt_js_events

(* CREEP *)
type creep = {
  id: int;
  mutable state : string;
  mutable x : int;
  mutable y : int;
}

let creep_id = ref 0
let creep_list : creep list ref = ref []

let init_1_creep () =
  creep_id := !creep_id + 1;
  let creep = {
    id = !creep_id;
    state = "alive";
    x = Random.int 500;
    y = Random.int 500;
  } in
  creep_list := creep :: !creep_list

let remove_creep_by_id id =
  creep_list := List.filter (fun creep -> creep.id <> id) !creep_list

let update_creep_state id new_state =
  let updated_list = List.map (fun creep ->
    if creep.id = id then { creep with state = new_state } else creep
  ) !creep_list in
  creep_list := updated_list
  
let create_creep_element creep =
  let style = Printf.sprintf "left:%dpx; top:%dpx;" creep.x creep.y in
  let attributes = [a_class ["creep"]; a_style style] in
  div ~a:attributes []


let add_creeps_to_dom () =
  let board_opt = Js_of_ocaml.Dom_html.getElementById_coerce "board" Js_of_ocaml.Dom_html.CoerceTo.element in
  match board_opt with
  | Some board -> 
    List.iter (fun creep ->
      let creep_element = create_creep_element creep in
      let creep_dom_node = Html.to_dom_node creep_element in
      Js_of_ocaml.Dom.appendChild board creep_dom_node
    ) !creep_list
  | None -> print_endline "Board not found"


  
let print_creep_list () =
  List.iter (fun creep -> print_endline ("creep id: " ^ (string_of_int creep.id))) !creep_list

let init_client () =
  print_endline "init_client";
  (* init creep and add them to the creep list *)
  for i = 0 to 3 do
    init_1_creep ()
  done;
  print_creep_list ();
  (* add creep to the board *)
  add_creeps_to_dom ();
]




(* SERVER SIDE *)
[%%server
open Eliom_content
open Html.D

module H42n42_app =
  Eliom_registration.App (
  struct
    let application_name = "h42n42"
    let global_data_path = None
  end)

let init_river =
  div ~a:[a_class ["river"]][
  ]

let init_ground = 
  div ~a:[a_class ["ground"]][]

  let init_hospital =
    div ~a:[a_class ["hospital"]] [
      div ~a:[a_class ["white_cross"]; a_id "left_cross"] [];
      div ~a:[a_class ["white_cross"]; a_id "middle_cross"] [];
      div ~a:[a_class ["white_cross"]; a_id "right_cross"] [];
    ]

let init_board =
  div ~a:[a_class [""]] [
    div ~a:[a_class ["board"]; a_id "board"] [
      init_river;
      init_ground;
      init_hospital;
    ]
  ]

let page =
  body [
    div ~a:[a_class ["wrap"]] [
      div ~a:[a_class ["title"]] [
        h1 [txt "H42N42"]
      ];
      init_board;
    ]
  ]

let main_service =
  Eliom_service.create
    ~path:(Eliom_service.Path [])
    ~meth:(Eliom_service.Get Eliom_parameter.unit)
    ()

let () =
  H42n42_app.register
    ~service:main_service
    (fun () () ->
      let _ = [%client (init_client () : unit)] in
      Lwt.return
        (Eliom_tools.D.html
          ~title:"h42n42"
          ~css:[["css";"h42n42.css"]]
          Html.D.(page)))

]